"""
Copyright 2022 Edward Kopp <edward@edwardkopp.com>

This program is free software: you can redistribute it and/or modify
it under the terms of the GNU General Public License as published by
the Free Software Foundation, either version 2 of the License, or
(at your option) any later version.

This program is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
GNU General Public License for more details.

You should have received a copy of the GNU General Public License
along with this program. If not, see <https://www.gnu.org/licenses/>.
"""


from os.path import join, isdir
from shutil import copytree, rmtree
from pathlib import Path
from json import load


class KeyboardsJson:

    ROOT = "keyboards"

    _JSON_PATH = join(ROOT, "keyboards.json")

    _COMMON_DIR = "common"
    COMMON = join(ROOT, _COMMON_DIR)

    _KEYBOARD_KEY = "kb"
    _KEYMAP_KEY = "km"

    _EK_USER = "edwardkopp"

    def __init__(self):
        with open(self._JSON_PATH, "r") as file:
            self._data = load(file)
        if self._COMMON_DIR in self._data:
            del self._data[self._COMMON_DIR]

    @property
    def list(self) -> list[str]:
        """
        Property for list of registered keymaps

        :return: list of registered keymap labels
        """
        return list(self._data.keys())

    def get_data(self, label: str) -> tuple[str, str, bool]:
        """
        Get tuple of two string values for the keys kb and km associated with the given label,
        indexed respectively.

        :param label: registered keymap label to get data for
        :return: tuple of keyboard value, keymap value, and boolean indicating use of headers files in common directory
        """
        keyboard = self._data[label][self._KEYBOARD_KEY]
        keymap = self._data[label][self._KEYMAP_KEY]
        use_common = keymap is None
        keymap = self._EK_USER if use_common else keymap
        return keyboard, keymap, use_common

    def uses_common(self, label: str) -> bool:
        return self.get_data(label)[-1]


class KeyboardsBank(KeyboardsJson):

    _QMK_KEYBOARD_DIR = "keyboards"
    _QMK_KEYMAP_DIR = "keymaps"
    _QMK_DIR = "qmk_firmware"
    _QMK_PATH = join(Path.home(), _QMK_DIR, _QMK_KEYBOARD_DIR)

    def __init__(self):
        if not isdir(self._QMK_PATH):
            raise NotADirectoryError("QMK firmware directory is missing.")
        KeyboardsJson.__init__(self)
        self._selected_label: str | None = None

    def select_label(self, label: str) -> None:
        """
        Accepts string label of registered keyboard and prepares it for use.

        :param label: string label of registered keyboard
        """
        lowercase_label = label.lower()
        if lowercase_label not in self.list:
            self._selected_label = None
            raise KeyError("Keymap with given label does not exist.")
        self._selected_label = lowercase_label

    def _require_select_label(self) -> None:
        """
        To be placed in public methods where a keyboard selection is required.

        :raise TypeError: if selected label is not registered
        """
        if self._selected_label is None:
            raise TypeError("A label must be selected before calling.")

    def deploy_keymap(self) -> None:
        """
        Place files of a registered keymap into the QMK directory
        for firmware compilation.

        :raise NotADirectoryError: if keymap files are not internally available
        """
        self._require_select_label()
        source_dir = join(self.ROOT, self._selected_label)
        if not isdir(source_dir):
            raise NotADirectoryError
        destination_dir = self._locate_qmk_keymap_dir(check_keymap=False)
        rmtree(destination_dir, True)
        copytree(source_dir, destination_dir)
        if self.uses_common(self._selected_label):
            copytree(self.COMMON, destination_dir, dirs_exist_ok=True)

    def update_keymap(self) -> None:
        """
        Read from the QMK directory and update registered keymap files
        for the registered keymap with the associated given label.

        :raise KeyError: if specified keymap name is not registered
        :raise NotADirectoryError: if keymap is not found in the QMK directory
        """
        self._require_select_label()
        if self.uses_common(self._selected_label):
            raise ValueError
        source_dir = self._locate_qmk_keymap_dir(check_keymap=True)
        destination_dir = join(self.ROOT, self._selected_label)
        rmtree(destination_dir, True)
        copytree(source_dir, destination_dir)

    def compile_command(self) -> str:
        """
        Get compile command for a registered keymap.

        :return: string for QMK compile command
        """
        self._require_select_label()
        return "qmk compile -kb {} -km {}".format(*self.get_data(self._selected_label))

    def _locate_qmk_keymap_dir(self, check_keymap: bool) -> str:
        """
        Confirm presence of keymap directories within QMK directory
        and return full path of keymap registered under given name.

        :param check_keymap: require registered keymap to already exist in QMK directory
        :return: path to QMK keymap directory
        :raise NotADirectoryError: if keymap directory check fails
        """
        keyboard, keymap, _ = self.get_data(self._selected_label)
        path_list_extension = [self._QMK_KEYMAP_DIR]
        minimum_path_len = 2
        if check_keymap:
            minimum_path_len = 3
            path_list_extension += [keymap]
        keymap_path_list: list = keyboard.replace("\\", "/").split("/") + path_list_extension
        while len(keymap_path_list) >= minimum_path_len:
            if isdir(join(self._QMK_PATH, *keymap_path_list)):
                if not check_keymap:
                    keymap_path_list += [keymap]
                return join(self._QMK_PATH, *keymap_path_list)
            keymap_path_list.pop(0-minimum_path_len)
        raise NotADirectoryError("Cannot find keymap directory.")


class Cli:

    def __init__(self):
        self._loop_active = True
        try:
            self._internal = KeyboardsBank()
        except NotADirectoryError:
            print("QMK firmware directory is missing from the user's home directory.")
            print("Use QMK MSYS/CLI to run the \"qmk setup\" command before running this program.")
            print()
            input("Press enter to exit the program... ")
            raise NotADirectoryError

    def run(self) -> None:
        print("Use the \"help\" command for a list of available commands.")
        while self._loop_active:
            self._command()

    def _command(self) -> None:
        invalid = False
        raw_command = input("> ").split(" ", 1)
        action = raw_command[0]
        if len(raw_command) < 2:
            match action:
                case "help":
                    self._help()
                case "exit":
                    self._loop_active = False
                case "list":
                    self._list_keymaps()
                case _:
                    invalid = True
        else:
            name_argument = raw_command[1]
            match action:
                case "deploy":
                    self._registered_action(name_argument, True)
                case "update":
                    self._registered_action(name_argument)
                case _:
                    invalid = True
        if invalid:
            print("Invalid command. Try again.")
        if self._loop_active:
            print()

    @staticmethod
    def _help() -> None:
        print("help - displays this message")
        print("exit - quit this program")
        print("list - list labels of registered keymaps")
        print("deploy <label> - deploy keymap associated with given label")
        print("update <label> - update keymap associated with given label")

    def _list_keymaps(self) -> None:
        if len(self._internal.list) == 0:
            print("There are no registered keymaps.")
        else:
            for name in self._internal.list:
                print(name)

    def _registered_action(self, label: str, deploying: bool = False) -> None:
        try:
            self._internal.select_label(label)
        except KeyError:
            print("Invalid \"label\" parameter. Try again.")
            return
        if deploying:
            try:
                self._internal.deploy_keymap()
                print("Run \"{}\" in QMK CLI/MSYS to compile the keymap.".format(self._internal.compile_command()))
            except NotADirectoryError:
                print("Missing keymap files for deploying.")
            return
        try:
            self._internal.update_keymap()
            print("Keymap internally updated.")
        except NotADirectoryError:
            print("Missing keymap within QMK directory to update from.")
        except ValueError:
            print("This keymap does not support updating from the QMK directory.")


if __name__ == "__main__":
    try:
        app = Cli()
    except NotADirectoryError:
        pass
    else:
        app.run()
