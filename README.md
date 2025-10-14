# A Simple PostgreSQL GUI Client


**PQVIEW** is a lightweight, native Windows desktop application written in C that serves as a basic viewer for PostgreSQL databases. It demonstrates how to connect a C application to a PostgreSQL backend using the `libpq` library and the native Windows API (Win32).

## REQUEREMENTS

- Visual Studio With DESKTOP C++ Installed
- Cmake
- Ninja
- PostgreSQL Installed
- Code Editor (Opsional 😂)

## Getting Started

These instructions will get you a copy of the project up and running on your local machine for development and testing purposes.

**Clone the repository:**

```sh
    git clone <your-repo-url>
    cd Belajar
```

**Create a build directory:**

```sh
    mkdir build
    cd build
```

**Configure the build with CMake:**
    Make sure to replace `"YOUR_POSTGRESQL_ROOT"` with the actual path to your PostgreSQL installation (e.g., `"C:\Program Files\PostgreSQL\16"`).
    
```sh
    cmake .. -DPostgreSQL_ROOT="YOUR_POSTGRESQL_ROOT" -G Ninja
```

**Compile the application:**

 ```sh
    ninja
```

## 🏃‍♂️ Running PQVIEW

After a successful build, you can find the executable inside the `build` directory.

```sh
.\PQVIEW.exe
```

Upon launching, the application will attempt to connect to your local PostgreSQL database. If successful, it will display the database version.
