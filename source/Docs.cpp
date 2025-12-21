#include <iostream>
#include <string>
#include "states.hpp"
#include "Docs.hpp"

bool Docs::toExit() {
    char choice;
    std::cin >> choice;

    if (choice == 'e'){
        state.clearScreen();
        return true;
    }
    return false;
}

void Docs::TaskerDocs(){
    std::cout << "\n";
    std::cout << R"(
SQC TASKER

Is a task manager
to add a task you press 1 (add task)
then you write a title for the task you want to add
after you add the description of the task
when done you could access the list of the tasks
press 2 to acess the tasks list
to delete a task press 3 and set the task number 
    )";
}

void Docs::ExcessDocs(){
    std::cout << "\n";
    std::cout << R"(
SQC EXCESS
Is a data manager
it needs a ID - to identify the data 
a Type - what the data is about
and a Content - the actual data that will be allocatted on it

to add a ID you press 1
then you write the name of the ID you want to add
then you press 2 to add the Type of the data you want to put - needs to be specified
and the Content on the Type you created
to access the datas press 3 to access the specified ID list 
to delete a data you press 4, and select a ID and the type
)";
}

void Docs::CrawlerDocs(){
    std::cout << "\n";
    std::cout << R"(
SQC CRAWLER
Is a File Searcher 
it needs a Root - to start looking 
and a File Name - the file who will be looked for

to search for a specific file type 1 (Search File)
then you write the Root you want to start
and the File Name on the Root you specified 
then it will return the path of the file
)";
}

void Docs::AtlasDocs(){
    std::cout << "\n";
    std::cout << R"(
SQC ATLAS
Is a Link Manager 
it needs a link - to open in the browser
and a name - to identify the link

to add a link type 1 (add link)
then you write the name fot the link
to open the link type 2 (open link)
then it will open in your browser
to delete a link type 4 (delete ) 
)";
}

void Docs::VaultDocs(){
    std::cout << "\n";
    std::cout << R"(
SQC VAULT
Is a Password Manager and a Password Verifier 

there are two types simetric and hash cryptography
the first one is for normal passwords
the second one is for verify the password (for example a login)

to add a password type 1 (add password)
and give a master key, for edit after the passwords
to check your passwords just type 2, for the simetric ones
for the hash ones is not possible see it
to delete a link type 6 or 7 to delete one password (depending for what you want)

it uses the library libsodium to cryptography
check the source code in this link:
https://github.com/jedisct1/libsodium
)";
}
void Docs::EditorDocs(){
    std::cout << "\n";
    std::cout << R"(
Micro Editor
Is a text and code editor
and is embedded with the SQC Core
to access it just type 'sqc editor' and the micro editor will open
is simple to use and looks almost like the Neovim
to see the commands just check the help function on the editor itself

is a third party project under the MIT license
there is no modification on the source code
it was only included the final binaries
the author of the project is Zachary Yedidia

to see the source code or modify it
check the link of the project below
https://github.com/zyedidia/micro
)";
}

void Docs::AboutDocs(){
	std::cout << "\n";
	std::cout << R"(
This Project uses another projects to help
make better use of it
some of them are:

libsodium - a cryptography library, under the MIT License
link: https://github.com/jedisct1/libsodium

Micro Editor - a terminal editor, write in Go, under the MIT License
https://github.com/zyedidia/micro

all rights are reserved for the respective creators of the projects ahead
	)";
}
