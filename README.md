# ReadHub

ReadHub is a locally hosted digital bookshelf application that allows users to manage their personal book collection, read PDFs, rate books, and write reviews.

## Main Features

- User accounts and authentication
- Create and manage a personal digital bookshelf
- Add and organize books
- Upload and read book PDFs
- Search and browse books
- View book information
- Rate books using a 5-star rating system
- Write and manage personal reviews


## Technology Stack

- **Programming Languages:** C++, JavaScript
- **Frontend:** Qt
- **Backend:** Qt / C++
- **Database:** MySQL

## Team Members

- Mahsa Fazli (former)
- Gyasi Darbeau
- Riley Judge
- Jingting Xu

## Project Status

🚧 **Work in Progress**

ReadHub is currently being developed as a university group project.

## Repository Structure

The repository structure will be expanded as development progresses.

## Development Workflow

ReadHub uses GitHub for version control and team collaboration.

main — main project branch.

iteration_1 — shared branch for the first development iteration.

Individual development branches (such as qt-mysql-integration) — used for implementing assigned tasks.

Team members develop and commit their changes on separate branches using descriptive commit messages.

Completed work is submitted through pull requests for review before being merged into iteration_1.

The team will integrate and test the implemented features before merging the iteration into main.

## Setup and Running Instructions

### Requirements
- Windows
- Qt 6 with Qt Widgets and Qt SQL
- Qt Creator
- CMake
- MinGW C++ compiler
- MySQL Server
- Qt MySQL (QMYSQL) driver

### Running the Application
1. Open `ReadHub/CMakeLists.txt` in Qt Creator.
2. Select a compatible Qt 6 MinGW kit.
3. Configure and build the project.
4. Run the application from Qt Creator.
5. Verify that the application connects successfully to MySQL.

**Note:** The application is still under development. Additional setup instructions may be needed as features are integrated.

## Testing

ReadHub will use automated tests and manual testing to verify that implemented features work correctly.

### Running Tests

Automated tests are being prepared as part of Iteration 1. The exact commands for running them will be added once the testing setup is finalized.

### Initial Testing Areas

- Database connection and book information storage
- User registration and login
- PDF upload and reading
- Bookshelf display and search

Test results and any identified issues will be documented as part of the P2 deliverable.
