# Target toolchain manifest

The final Xbox 360 build adapter must be configured from known toolchain facts,
not guessed SDK names or paths.

Copy `config/toolchain.example.ini` to a local, ignored
`config/toolchain.local.ini` and fill it only after the compatible target
environment is selected.

Required facts:

- C/C++ compiler path
- linker path
- XEX generation tool/step
- include directories
- library directories
- module-entry convention
- debug-output mechanism

Do not commit proprietary SDK paths, headers, libraries, executables, license
data, or credentials.

The portable source remains buildable/documentable without this manifest; the
manifest is only for the target-XEX adapter.
