# Windows PC test setup

Run `tools\\prepare-pc-test.bat`.

It checks whether Microsoft MSVC C++ build tools are installed. If missing, install **Visual Studio Build Tools** and select **Desktop development with C++** in Visual Studio Installer.

After the check passes, open a **Developer Command Prompt for Visual Studio** in the repository and run `tools\\run-pc-smoke-test.bat`.

Expected success ends with `[PASS] Safe first-test build identity is valid.`

This is a Windows host test only. It does not create an Xbox 360 XEX or validate controller/audio/Party Chat/Game Chat hardware behavior.
