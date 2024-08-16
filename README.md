# HTTP Server with Thread Pool and Dynamic Responses

## Project Overview

This project involves the development of a custom HTTP server capable of handling client requests efficiently. The server is designed to respond to `GET` requests for HTML files and provides appropriate HTTP headers and status codes. To enhance performance and manage multiple client connections efficiently, the server uses a reusable worker thread pool. Additionally, the server supports dynamic HTTP responses, including proper error handling for various status codes like `200 OK` and `404 Not Found`.

## Table of Contents

- [Project Overview](#project-overview)
- [Features](#features)
- [System Requirements](#system-requirements)
- [Installation](#installation)
- [Usage](#usage)
- [Contribution Guidelines](#contribution-guidelines)
- [License](#license)

## Features

- **GET Request Handling:** The server responds to `GET` requests by serving HTML files with the appropriate HTTP headers and status codes.
- **Reusable Worker Thread Pool:** Implements a thread pool to efficiently manage multiple client connections, reducing server overhead and improving performance.
- **Dynamic HTTP Responses:** Supports dynamic generation of HTTP responses with proper status codes, including common responses such as `200 OK` and `404 Not Found`.
- **Error Handling:** Provides comprehensive error handling, ensuring clients receive appropriate status codes and error messages.

## System Requirements

- **Operating System:** Linux, macOS, or Windows (with a suitable C/C++ compiler).
- **Compiler:** GCC or Clang for Linux/macOS, or MSVC for Windows.
- **Libraries:** POSIX threads (pthreads) for thread management (Linux/macOS). On Windows, use Windows threading libraries.

