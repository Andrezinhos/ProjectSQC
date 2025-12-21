import std.stdio;
import std.string;

import crawler.explorer;

void main() {
    writeln("Type the file ");
    string fileName = readln().chomp;
    
    if (!list("C:\\", fileName)){
        writeln("Not find the file");
    }
}
