# My QMK Stuff

This repository contains keymaps I use for any QMK keyboards I have.
Keymap files can be found within the `keyboards` directory.
I have a simple Python script, `main.py`, to manage keymap files.
Use it to work with keymaps and the QMK firmware directory.

Please note that `main.py` only works when the
[QMK firmware](https://github.com/qmk/qmk_firmware) repository is in
the user's home directory.

# Registering Your Own Keymaps

In `keyboards.json` within the `keyboards` directory, keyboard entries
will appear as follows:

```json
{
    "keymap_label_0": {
        "kb": "qmk_keyboard_0",
        "km": "qmk_keymap_0"
    },
    "keymap_label_1": {
        "kb": "qmk_keyboard_1",
        "km": "qmk_keymap_1"
    }
}
```

The labels, `keymap_label_0` and `keymap_label_1`, should be directory
names within the `keyboards` directory of this repository. These internal
directories will eventually hold the keymap files.

The keys `kb` and `km` associated with each label should match the `kb`
and `km` arguments for compiling the desired keymap with `qmk compile`
in [QMK CLI](https://github.com/qmk/qmk_cli)/
[MSYS](https://github.com/qmk/qmk_distro_msys).
Below is an example keymap, labeled `preonic`, corresponding
with the command `qmk compile -kb preonic/rev3_drop -km edwardkopp`:

```json
{
    "preonic": {
        "kb": "preonic/rev3_drop",
        "km": "edwardkopp"
    }
}
```

After adding your keymap details to `keyboards.json`, you can run `main.py`
and execute the command `update <label>`, where `<label>` is the label of
your keymap, to copy keymap files from the QMK firmware repository in the
user's home directory.
