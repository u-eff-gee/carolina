#     This file is part of carolina.
#
#    carolina is free software: you can redistribute it and/or modify it under the terms of 
#    the GNU General Public License as published by the Free Software Foundation, 
#    either version 3 of the License, or (at your option) any later version.
#
#    carolina is distributed in the hope that it will be useful, but WITHOUT ANY 
#    WARRANTY; without even the implied warranty of MERCHANTABILITY or 
#    FITNESS FOR A PARTICULAR PURPOSE. See the GNU General Public License for 
#    more details.
#
#    You should have received a copy of the GNU General Public License along with 
#    carolina. If not, see <https://www.gnu.org/licenses/>.

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