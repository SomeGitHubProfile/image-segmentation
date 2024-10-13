Большая задача (2 семестр, ФКИ)
# Usage
Input path to png file. Program will segment image and store segmented image in output_images folder. It will also store some temporary photos.
# Configs
Program supports configs. When started, it always searches for default.cfg. If it doesn't exist, it creates default.cfg and applies default settings.
If default.cfg exists, program will load it and apply settings from it. Then you can modify settings in default.cfg.
If param "config" in default.cfg doesn't equal to "this" or "default.cfg" and there is config, which name equals to the "config" param's value, program will load that config.
For example, if default.cfg contains string "config: arm.cfg" and there is arm.cfg in that folder, program will load arm.cfg.
Only default.cfg can redirect loading to another config.
If config doesn't contain some params, they will be set do default values.
If config contains some lines, that aren't params, the program will ignore them.
# Config params
* config: the name of config that should be loaded (used only in default.cfg). Use "config: this" to load default.cfg config.
* median filter: "disabled"/"enabled". Enable to use median filter before gaussian filter.
* gaussian kernel: "3x3"/"5x5"/"5x5_low_value". Different kernels for gaussian filter. "3x3" is recommended for images with a huge number of little details.
* sobel kernel: "3x3"/"5x5". Different sobel kernels.
* boundaries detection strength: an integer in [0, 255]. A pixel is boundary, if it's gray color (after sobel filter) is >= <ins>boundaries detection strength</ins>.
* boundaries radius: an integer in [0, 255]. A pixel is boundary, if there are more than <ins>boundaries radius</ins> pixels (true boundaries) around it (in square <ins>boundaries radius</ins> * <ins>boundaries radius</ins>.
# Build
1. Download Microsoft Visual Studio (NOT Visual Studio Code).
2. Open it and click "Continue without code".
3. Select File &rarr; New &rarr; Project From Existing Code.
4. Select "project type": "Visual C++".
5. Click "Next".
6. Select "project location": the folder where you cloned this repository.
7. Select "file types": we need "\*.c" and "\*.h", they are included by default, so you can skip this step.
8. Click "Next".
9. Select "project build": "Use Visual Studio" (set by default).
10. Select "project type": "Console application".
11. We've configured our project, click "Next" until the build starts.
12. Change "Debug" to "Release".
13. Select "Build" &rarr; "Build solution".
14. You will see your exe-file in the "Release" folder.
15. Done!
