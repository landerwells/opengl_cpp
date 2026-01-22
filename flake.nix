{
  description = "OpenGL C++ project with Wayland support";

  inputs = {
    nixpkgs.url = "github:NixOS/nixpkgs/nixos-unstable";
    flake-utils.url = "github:numtide/flake-utils";
  };

  outputs = { self, nixpkgs, flake-utils }:
    flake-utils.lib.eachDefaultSystem (system:
      let
        pkgs = nixpkgs.legacyPackages.${system};
      in
      {
        devShells.default = pkgs.mkShell {
          packages = with pkgs; [
            # Build tools
            cmake
            gcc
            pkg-config
            clang-tools

            # Wayland dependencies
            wayland
            wayland-protocols
            wayland-scanner
            libxkbcommon

            # X11 dependencies (fallback)
            xorg.libX11
            xorg.libXrandr
            xorg.libXinerama
            xorg.libXcursor
            xorg.libXi

            # OpenGL
            libGL
            libGLU
          ];

          shellHook = ''
            export LD_LIBRARY_PATH=${pkgs.lib.makeLibraryPath [
              pkgs.wayland
              pkgs.libxkbcommon
              pkgs.libGL
              pkgs.xorg.libX11
            ]}:$LD_LIBRARY_PATH

            echo "OpenGL C++ development environment loaded"
            echo "Wayland and X11 support enabled"
          '';
        };
      }
    );
}
