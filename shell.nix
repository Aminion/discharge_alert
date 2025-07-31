# my-arduino-project/shell.nix
{ pkgs ? import <nixpkgs> {} }: # Uses your system's default nixpkgs channel

pkgs.mkShell {
  name = "platformio-cli-env";
  packages = with pkgs; [
    platformio
    picocom
    minicom
    #avrdude
  ];

  # This shellHook runs every time you enter the nix-shell.
  # It sets up environment variables for PlatformIO.
  shellHook = ''
    echo "Entering PlatformIO CLI development environment."
    export PATH="${pkgs.micronucleus}/bin:$PATH"
    # Direct PlatformIO to store its platform, framework, and library data
    # within your project's .platformio folder. This keeps it self-contained
    # and prevents global pollution of your Nix store.

    export PLATFORMIO_CORE_DIR="$PWD/.platformio"
    mkdir -p "$PLATFORMIO_CORE_DIR" # Ensure the directory exists
  '';
}