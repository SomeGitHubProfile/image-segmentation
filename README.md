Большая задача (2 семестр, ФКИ)
# Usage
Input path to png file. Program will segment image and store segmented image in output_images folder. It will also store some temporary photos.
# Configs
Program supports configs. When started, it always searches for default.cfg. If it doesn't exist, it creates default.cfg and applies default settings.
If default.cfg exists, program will load it and apply settings from it.
If param "config" in default.cfg doesn't equal to "this" or "default.cfg" and there is config, which name equals to the "config" param's value, program will load that config.
For example, if default.cfg contains string "config: arm.cfg" and there is arm.cfg in that folder, program will load arm.cfg.
Only default.cfg can redirect loading to another config.
If config doesn't contain some params, they will be set do default values.
If config contains some lines, that aren't params, the program will ignore them.
# Config settings
* config: name of config that should be loaded (used only in default.cfg). Use "config: this" to load this config.
* median filter: "disabled"/"enabled". Enable, to use median filter before gaussian filter.
* gaussian kernel: "3x3"/"5x5"/"5x5_low_value". Different kernels for gaussian filter.
* sobel kernel: "3x3"/"5x5". Different sobel kernels.
* boundaries detection strength: an integer in [0, 255]. A pixel is boundary, if it's gray color (after sobel filter) is >= <ins>boundaries detection strength</ins>.
* boundaries radius: an integer in [0, 255]. A pixel is boundary, if there are more than <ins>boundaries radius</ins> pixels (true boundaries) around it (in square <ins>boundaries radius</ins> * <ins>boundaries radius</ins>.
