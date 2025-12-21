TARGET = bin/sqc

CXX = g++

CXXFLAGS = -Wall -std=c++17 -Iheaders -Ilibsodium/include
LDFLAGS = -Llibsodium/include/lib -lsodium

CORE = source/core.cpp source/mainMenu.cpp
TASKER = source/TaskerMenu.cpp source/Tasker.cpp
EXCESS = source/Excess.cpp source/ExcessMenu.cpp 
CRAWLER = source/CrawlerMenu.cpp source/Crawler.cpp
ATLAS = source/Atlas.cpp source/AtlasMenu.cpp  
DOCS = source/Docs.cpp source/DocsMenu.cpp
CHRONO = source/Chrono.cpp source/ChronoMenu.cpp
VAULT = source/Vault.cpp source/VaultMenu.cpp

SRC = $(CORE) $(TASKER) $(EXCESS) $(DOCS) $(CRAWLER) $(ATLAS) $(CHRONO) $(VAULT)

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