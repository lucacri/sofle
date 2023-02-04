# Sofle Keyboard

qmk compile -kb luca/keyhive -km lucacri:avrdude-split-left && qmk compile -kb luca/keyhive -km lucacri:avrdude-split-right

## For the VIA setup

First use the keymaps/lucacri/via_setup.json. Then apply the lucacri_sofle.json.

Once all is done, you can export a keymap.c by doing

```
qmk via2json -kb luca/keyhive -km lucacri:avrdude-split-left -o keymaps/lucacri/keymap-c.json -l keymaps/lucacri/via-setup.json keymaps/lucacri/lucacri_sofle.json

# go to https://jhelvy.shinyapps.io/qmkjsonconverter/ and upload keymaps/lucacri/keymap-c.json
# take the file and rename the layers in keymap.c
```
