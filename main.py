#!/usr/bin/env python3

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


class Keyboards:

    class _Json:

        KEYBOARD_KEY = "kb"
        KEYMAP_KEY = "km"

    _KEYMAP_DIR = "keymaps"
    _DIR = "keyboards"
    _JSON_PATH = join(_DIR, "keyboards.json")
    _QMK_DIR = "qmk_firmware"
    _QMK_KEYBOARDS_DIR = "keyboards"
    _QMK_PATH = join(Path.home(), _QMK_DIR, _QMK_KEYBOARDS_DIR)

    def __init__(self):
        if not isdir(self._QMK_PATH):
            raise NotADirectoryError("QMK firmware directory is missing.")
        with open(self._JSON_PATH, "r") as file:
            self._data = load(file)

    @property
    def list(self) -> list:
        """
        Property for list of registered keymaps

        :return: list of registered keymap labels
        """
        return list(self._data.keys())

    def deploy_keymap(self, label: str) -> None:
        """
        Place files of a registered keymap into the QMK directory
        for firmware compilation.

        :param label: label of registered keymap to deploy
        :raise KeyError: if specified keymap name is not registered
        :raise NotADirectoryError: if keymap files are not internally available
        """
        label = self._label_check(label)
        source_dir = join(self._DIR, label)
        destination_dir = self._locate_keymap_dir(label, check_keymap=False)
        rmtree(destination_dir, True)
        copytree(source_dir, destination_dir)

    def update_keymap(self, label: str) -> None:
        """
        Read from the QMK directory and update registered keymap files
        for the registered keymap with the associated given label.

        :param label: label of registered keymap to update
        :raise KeyError: if specified keymap name is not registered
        :raise NotADirectoryError: if keymap is not found in the QMK directory
        """
        label = self._label_check(label)
        source_dir = self._locate_keymap_dir(label, check_keymap=True)
        destination_dir = join(self._DIR, label)
        rmtree(destination_dir, True)
        copytree(source_dir, destination_dir)

    def compile_command(self, label: str) -> str:
        """
        Get compile command for a registered keymap.

        :param label: label of registered keymap to get command for
        :return: string for QMK compile command
        """
        return "qmk compile -kb {} -km {}".format(*self._json_data(label))

    def _label_check(self, label: str) -> str:
        label = label.lower()
        if label not in self.list:
            raise KeyError("Keymap with given label does not exist.")
        return label

    def _locate_keymap_dir(self, label: str, check_keymap: bool) -> str:
        """
        Confirm presence of keymap directories within QMK directory
        and return full path of keymap registered under given name.

        :param label: keymap label as registered
        :param check_keymap: require registered keymap to already exist in QMK directory
        :return: path to QMK keymap directory
        :raise NotADirectoryError: if keymap directory check fails
        """
        keyboard, keymap = self._json_data(label)
        path_list_extension = [self._KEYMAP_DIR]
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

    def _json_data(self, label: str) -> tuple[str, str]:

        def _from_label(key: str) -> str:
            return self._data[label][key]

        return _from_label(self._Json.KEYBOARD_KEY), _from_label(self._Json.KEYMAP_KEY)


class Cli:

    def __init__(self):
        self._loop_active = True
        self._do_not_run = False
        try:
            self._internal = Keyboards()
        except NotADirectoryError:
            self._do_not_run = True

    def run(self) -> None:
        if self._do_not_run:
            print("QMK firmware directory is missing from the user's home directory.")
            print("Use QMK MSYS/CLI to run the \"qmk setup\" command before running this program.")
            print()
            input("Press enter to exit the program... ")
            return
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
            if deploying:
                self._internal.deploy_keymap(label)
                print("Run \"{}\" in QMK CLI/MSYS to compile the keymap.".format(self._internal.compile_command(label)))
            else:
                self._internal.update_keymap(label)
                print("Keymap internally updated.")
        except KeyError:
            print("Invalid \"label\" parameter. Try again.")
        except NotADirectoryError:
            # Only can occur when deploying == False
            print("Missing keymap within QMK directory to update from.")


if __name__ == "__main__":
    app = Cli()
    app.run()
