FILES=\
`ls include/analysis/*.hpp`" "\
`ls include/experiments/*.hpp`" "\
`ls include/detectors/*.hpp`" "\
`ls include/io/*.hpp`" "\
`ls include/modules/*.hpp`" "\
`ls include/programs/*.hpp.in`" "\
`ls include/test/*.hpp.in`" "\
`ls source/analysis/*.cpp`" "\
`ls source/detectors/*.cpp`" "\
`ls source/io/*.cpp`" "\
`ls source/modules/*.cpp`" "\
`ls source/programs/*.cpp`" "\
`ls source/test/*.cpp`" "\

for FILE in $FILES
do
    echo Formatting $FILE ...
    clang-format -i -style="{IndentWidth: 4, TabWidth: 4}" $FILE
done