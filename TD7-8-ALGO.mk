##
## Auto Generated makefile by CodeLite IDE
## any manual changes will be erased      
##
## Debug
ProjectName            :=TD7-8-ALGO
ConfigurationName      :=Debug
WorkspacePath          :=C:/Users/ProgrammationS5/CodeLiteProjects
ProjectPath            :=C:/Users/ProgrammationS5/CodeLiteProjects/TD7-8-ALGO
IntermediateDirectory  :=./Debug
OutDir                 := $(IntermediateDirectory)
CurrentFileName        :=
CurrentFilePath        :=
CurrentFileFullPath    :=
User                   :=Alexandre Zajac
Date                   :=28/08/2019
CodeLitePath           :="C:/Program Files/CodeLite"
LinkerName             :=C:/MinGW/bin/g++.exe
SharedObjectLinkerName :=C:/MinGW/bin/g++.exe -shared -fPIC
ObjectSuffix           :=.o
DependSuffix           :=.o.d
PreprocessSuffix       :=.i
DebugSwitch            :=-g 
IncludeSwitch          :=-I
LibrarySwitch          :=-l
OutputSwitch           :=-o 
LibraryPathSwitch      :=-L
PreprocessorSwitch     :=-D
SourceSwitch           :=-c 
OutputFile             :=$(IntermediateDirectory)/$(ProjectName)
Preprocessors          :=
ObjectSwitch           :=-o 
ArchiveOutputSwitch    := 
PreprocessOnlySwitch   :=-E
ObjectsFileList        :="TD7-8-ALGO.txt"
PCHCompileFlags        :=
MakeDirCommand         :=makedir
RcCmpOptions           := 
RcCompilerName         :=C:/MinGW/bin/windres.exe
LinkOptions            :=  -static
IncludePath            :=  $(IncludeSwitch). $(IncludeSwitch). 
IncludePCH             := 
RcIncludePath          := 
Libs                   := 
ArLibs                 :=  
LibPath                := $(LibraryPathSwitch). 

##
## Common variables
## AR, CXX, CC, AS, CXXFLAGS and CFLAGS can be overriden using an environment variables
##
AR       := C:/MinGW/bin/ar.exe rcu
CXX      := C:/MinGW/bin/g++.exe
CC       := C:/MinGW/bin/gcc.exe
CXXFLAGS :=  -g -O0 -Wall $(Preprocessors)
CFLAGS   :=  -g -O0 -Wall $(Preprocessors)
ASFLAGS  := 
AS       := C:/MinGW/bin/as.exe


##
## User defined environment variables
##
CodeLiteDir:=C:\Program Files\CodeLite
Objects0=$(IntermediateDirectory)/main.c$(ObjectSuffix) $(IntermediateDirectory)/arbre.c$(ObjectSuffix) $(IntermediateDirectory)/utilitaires.c$(ObjectSuffix) $(IntermediateDirectory)/vecteur.c$(ObjectSuffix) 



Objects=$(Objects0) 

##
## Main Build Targets 
##
.PHONY: all clean PreBuild PrePreBuild PostBuild MakeIntermediateDirs
all: $(OutputFile)

$(OutputFile): $(IntermediateDirectory)/.d $(Objects) 
	@$(MakeDirCommand) $(@D)
	@echo "" > $(IntermediateDirectory)/.d
	@echo $(Objects0)  > $(ObjectsFileList)
	$(LinkerName) $(OutputSwitch)$(OutputFile) @$(ObjectsFileList) $(LibPath) $(Libs) $(LinkOptions)

MakeIntermediateDirs:
	@$(MakeDirCommand) "./Debug"


$(IntermediateDirectory)/.d:
	@$(MakeDirCommand) "./Debug"

PreBuild:


##
## Objects
##
$(IntermediateDirectory)/main.c$(ObjectSuffix): main.c $(IntermediateDirectory)/main.c$(DependSuffix)
	$(CC) $(SourceSwitch) "C:/Users/ProgrammationS5/CodeLiteProjects/TD7-8-ALGO/main.c" $(CFLAGS) $(ObjectSwitch)$(IntermediateDirectory)/main.c$(ObjectSuffix) $(IncludePath)
$(IntermediateDirectory)/main.c$(DependSuffix): main.c
	@$(CC) $(CFLAGS) $(IncludePath) -MG -MP -MT$(IntermediateDirectory)/main.c$(ObjectSuffix) -MF$(IntermediateDirectory)/main.c$(DependSuffix) -MM main.c

$(IntermediateDirectory)/main.c$(PreprocessSuffix): main.c
	$(CC) $(CFLAGS) $(IncludePath) $(PreprocessOnlySwitch) $(OutputSwitch) $(IntermediateDirectory)/main.c$(PreprocessSuffix) main.c

$(IntermediateDirectory)/arbre.c$(ObjectSuffix): arbre.c $(IntermediateDirectory)/arbre.c$(DependSuffix)
	$(CC) $(SourceSwitch) "C:/Users/ProgrammationS5/CodeLiteProjects/TD7-8-ALGO/arbre.c" $(CFLAGS) $(ObjectSwitch)$(IntermediateDirectory)/arbre.c$(ObjectSuffix) $(IncludePath)
$(IntermediateDirectory)/arbre.c$(DependSuffix): arbre.c
	@$(CC) $(CFLAGS) $(IncludePath) -MG -MP -MT$(IntermediateDirectory)/arbre.c$(ObjectSuffix) -MF$(IntermediateDirectory)/arbre.c$(DependSuffix) -MM arbre.c

$(IntermediateDirectory)/arbre.c$(PreprocessSuffix): arbre.c
	$(CC) $(CFLAGS) $(IncludePath) $(PreprocessOnlySwitch) $(OutputSwitch) $(IntermediateDirectory)/arbre.c$(PreprocessSuffix) arbre.c

$(IntermediateDirectory)/utilitaires.c$(ObjectSuffix): utilitaires.c $(IntermediateDirectory)/utilitaires.c$(DependSuffix)
	$(CC) $(SourceSwitch) "C:/Users/ProgrammationS5/CodeLiteProjects/TD7-8-ALGO/utilitaires.c" $(CFLAGS) $(ObjectSwitch)$(IntermediateDirectory)/utilitaires.c$(ObjectSuffix) $(IncludePath)
$(IntermediateDirectory)/utilitaires.c$(DependSuffix): utilitaires.c
	@$(CC) $(CFLAGS) $(IncludePath) -MG -MP -MT$(IntermediateDirectory)/utilitaires.c$(ObjectSuffix) -MF$(IntermediateDirectory)/utilitaires.c$(DependSuffix) -MM utilitaires.c

$(IntermediateDirectory)/utilitaires.c$(PreprocessSuffix): utilitaires.c
	$(CC) $(CFLAGS) $(IncludePath) $(PreprocessOnlySwitch) $(OutputSwitch) $(IntermediateDirectory)/utilitaires.c$(PreprocessSuffix) utilitaires.c

$(IntermediateDirectory)/vecteur.c$(ObjectSuffix): vecteur.c $(IntermediateDirectory)/vecteur.c$(DependSuffix)
	$(CC) $(SourceSwitch) "C:/Users/ProgrammationS5/CodeLiteProjects/TD7-8-ALGO/vecteur.c" $(CFLAGS) $(ObjectSwitch)$(IntermediateDirectory)/vecteur.c$(ObjectSuffix) $(IncludePath)
$(IntermediateDirectory)/vecteur.c$(DependSuffix): vecteur.c
	@$(CC) $(CFLAGS) $(IncludePath) -MG -MP -MT$(IntermediateDirectory)/vecteur.c$(ObjectSuffix) -MF$(IntermediateDirectory)/vecteur.c$(DependSuffix) -MM vecteur.c

$(IntermediateDirectory)/vecteur.c$(PreprocessSuffix): vecteur.c
	$(CC) $(CFLAGS) $(IncludePath) $(PreprocessOnlySwitch) $(OutputSwitch) $(IntermediateDirectory)/vecteur.c$(PreprocessSuffix) vecteur.c


-include $(IntermediateDirectory)/*$(DependSuffix)
##
## Clean
##
clean:
	$(RM) -r ./Debug/


