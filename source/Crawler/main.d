import std.stdio;
import std.string;
//import crawler.explorer;
import crawler.launcher;

void main() {
    writeln("Type the file ");
    string fileName = readln().chomp;
    
    if (!openList("C:\\Program Files", fileName)){
        writeln("Not find the file");
    }
}
