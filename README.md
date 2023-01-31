# Project APDFCreator

APDFCreator is an app designed to provide an easy way to create academic PDF documents using 
the WYSIWYG principle. It is still a work in progress and currently supports adding text,
images and formulae in LaTeX format.

## Dependencies

This app requires **latex** and **dvipng** packages to be installed on the system. 

You can set up LaTeX support on your Ubuntu installation by running:

`sudo apt install texlive-latex-extra dvipng`

On Windows, you can download and install the free [MiKTeX](https://miktex.org/) TeX distribution.

Make sure to add **latex** and **dvipng** packages to your _PATH_ environment variable.

### Note:

You will need to install the packages required by LaTeX upon first starting the APDFCreator.  

## Building

Download and install Qt 6.2.1 library (along with Qt Creator)

Position into the desired directory and clone the repository.

Open the project by opening the `CMakeLists.txt` file, and click on **Configure project**.

Change the build mode to **Release** and start building using the **Build->Build Project "APDF Creator"**

Move the built .exe file from build folder to a new one and run _pathToYourQtDirectory/windeployqt.exe pathToAPDFCreatorExe/APDFCreator.exe_

Copy **libstdc++-6.dll**, **libgcc_s_seh-1.dll** and **libwinpthread-1.dll** alongside APDFCreator.exe.

Building process completed.
