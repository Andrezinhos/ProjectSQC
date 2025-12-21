module crawler.explorer;
import std.stdio;
import std.string;
import std.file;
import std.algorithm.searching;
import std.path;
import std.process;

bool list(string dir, string target){
    try{
        foreach (entry; dirEntries(dir, SpanMode.shallow)){
            
            string path = entry.name;
            if (path.canFind("$Recycle.Bin") || 
                path.canFind("System Volume Information") ||
                // path.canFind("\\Windows") ||
                // path.canFind("\\Program Files") ||
                path.canFind("\\Program Files (x86)") ||
                path.canFind("\\Recovery") ||
                // path.canFind("\\Arquivos de Programas") ||
                path.canFind("\\ProgramData")) 
            { 
                continue;
            }
            if (entry.isDir){
                if (list(path, target)){
                    return true;
                }
            } else if (entry.isFile){
                if (baseName(path) == target){
                    writeln("Name: ", entry.name);
                    return true;
                }
            }
        }
    } catch (FileException e) {
        //writeln("Ignored: ", dir);
    }
    return false;
}
bool openList(string dir, string target){
    try{
        foreach (entry; dirEntries(dir, SpanMode.shallow)){
            
            string path = entry.name;
            if (path.canFind("$Recycle.Bin") || 
                path.canFind("System Volume Information") ||
                //path.canFind("\\Windows") ||
                path.canFind("\\Recovery") ||
                path.canFind("\\ProgramData")
                ) 
            { 
                continue;
            }
            if (entry.isDir){
                if (openList(path, target)){
                    return true;
                }
            } else if (entry.isFile){
                if (baseName(path) == target){
                    writeln("Name: ", entry.name);

                    spawnShell(path);
                    return true;
                }
            }
        }
    } catch (FileException e) {
        //writeln("Ignored: ", dir);
    }
    return false;
}