import std.stdio;
import std.string;
import std.conv;
import crawler.explorer;

void main() {
    writeln("Chose the option:");
    writeln("launch (1)");
    writeln("path (2)");
    string input = readln().chomp;
    int choice = to!int(input);
    
    if (choice == 1){
        writeln("Type the file: ");
        string fileName = readln().chomp;

        if (!openList("C:\\", fileName)){
            writeln("Not find the file");
        }
    }

    if (choice == 2) {
        writeln("Type the file: ");
        string fileName = readln().chomp;

        if (!list("C:\\", fileName)){
            writeln("Not find the file");
        }
    }
}
