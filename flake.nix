{
  description = "OpenGL C++ project with cross-platform support";
  
  inputs = {
    nixpkgs.url = "github:NixOS/nixpkgs/nixos-unstable";
    flake-utils.url = "github:numtide/flake-utils";
  };
  
  outputs = { self, nixpkgs, flake-utils }:
    flake-utils.lib.eachSystem [ "x86_64-linux" "aarch64-darwin" ] (system:
      let
        pkgs = nixpkgs.legacyPackages.${system};
        
        # Common dependencies for all platforms
        commonDeps = with pkgs; [
          cmake
          pkg-config
          clang-tools
          
          # OpenGL/Graphics libraries
          glfw
          glm
          
          # Additional libraries
          stb
        ];
        
        # Linux-specific dependencies
        linuxDeps = with pkgs; [
          gcc
          
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
        
        # macOS-specific dependencies
        darwinDeps = with pkgs; [
          # Clang is the default on macOS
        ];
        
        # Combine dependencies based on platform
        buildInputs = commonDeps 
          ++ (if pkgs.stdenv.isLinux then linuxDeps else [])
          ++ (if pkgs.stdenv.isDarwin then darwinDeps else []);
        
      in
      {
        devShells.default = pkgs.mkShell {
          packages = buildInputs;
          
          shellHook = if pkgs.stdenv.isLinux then ''
            export LD_LIBRARY_PATH=${pkgs.lib.makeLibraryPath [
              pkgs.wayland
              pkgs.libxkbcommon
              pkgs.libGL
              pkgs.xorg.libX11
              pkgs.glfw
            ]}:$LD_LIBRARY_PATH
            echo "OpenGL C++ development environment loaded (Linux)"
            echo "Wayland and X11 support enabled"
          '' else ''
            # macOS doesn't need LD_LIBRARY_PATH
            echo "OpenGL C++ development environment loaded (macOS)"
            echo "Using native macOS frameworks"
          '';
        };
        
        # Optional: define the actual package build
        packages.default = pkgs.stdenv.mkDerivation {
          pname = "opengl_cpp";
          version = "0.1.0";
          
          src = ./.;
          
          nativeBuildInputs = [ pkgs.cmake pkgs.pkg-config ];
          buildInputs = buildInputs;
          
          cmakeFlags = [
            "-DCMAKE_BUILD_TYPE=Release"
          ];
        };
      }
    );
}
