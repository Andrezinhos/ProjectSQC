TARGET = bin/sqc

CXX = g++

CXXFLAGS = -Wall -std=c++17 -Iheaders -Ilibsodium/include
LDFLAGS = -Llibsodium/include/lib -lsodium -Llibzip/lib -lzip

CORE = source/core.cpp source/mainMenu.cpp
TASKER = source/TaskerMenu.cpp source/Tasker.cpp
EXCESS = source/Excess.cpp source/ExcessMenu.cpp 
CRAWLER = source/CrawlerMenu.cpp
ATLAS = source/Atlas.cpp source/AtlasMenu.cpp  
DOCS = source/Docs.cpp source/DocsMenu.cpp
VAULT = source/Vault.cpp source/VaultMenu.cpp
MONITOR = source/Monitor.cpp source/MonitorMenu.cpp
SMASH = source/Smash.cpp source/SmashMenu.cpp

SRC = $(CORE) $(TASKER) $(EXCESS) $(DOCS) $(CRAWLER) $(ATLAS) $(VAULT) $(MONITOR) $(SMASH)

#OBJ = ${SRC:.cpp=.o}
OBJDIR = build
OBJ = $(patsubst source/%.cpp,$(OBJDIR)/%.o,$(SRC))

$(TARGET): $(OBJ)
	$(CXX) $(OBJ) -o $(TARGET) $(LDFLAGS)

# # Como compilar cada .cpp em .o
# %.o: %.cpp
# 	$(CXX) $(CXXFLAGS) -c $< -o $@
ifeq ($(OS),Windows_NT)
    MKDIR = if not exist $(OBJDIR) mkdir $(OBJDIR)
    RM = rmdir /S /Q
else
    MKDIR = mkdir -p $(OBJDIR)
    RM = rm -rf
endif

$(OBJDIR)/%.o: source/%.cpp
	@$(MKDIR)
	$(CXX) $(CXXFLAGS) -c $< -o $@
# Limpar arquivos gerados

clean:
	$(RM) -r $(OBJDIR) $(TARGET)
# 	del /Q /F origins/*.o bin/sqc.exe $(OBJ) $(TARGET)