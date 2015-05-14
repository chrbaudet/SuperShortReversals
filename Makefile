# /******************************************************************************/
# /*                                                                            */
# /*   This file is part of SuperShortReversals.                                */
# /*                                                                            */
# /*   SuperShortReversals is free software: you can redistribute it and/or     */
# /*   modify it under the terms of the GNU General Public License as published */
# /*   by the Free Software Foundation, either version 2 of the License, or     */
# /*   any later version.                                                       */
# /*                                                                            */
# /*   SuperShortReversals is distributed in the hope that it will be useful,   */
# /*   but WITHOUT ANY WARRANTY; without even the implied warranty of           */
# /*   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the            */
# /*   GNU General Public License for more details.                             */
# /*                                                                            */
# /*   You should have received a copy of the GNU General Public License        */
# /*   along with SuperShortReversals.                                          */
# /*   If not, see <http://www.gnu.org/licenses/>.                              */
# /*                                                                            */
# /******************************************************************************/

.SUFFIXES : .cpp

CPP=c++

STDLIB=c++11

CFLAGS=-Wall -g -O2 -std=$(STDLIB)

INCLUDES=-Iheaders

LIBRARIES=

SOURCES1=sscpssr_distance.cpp

SOURCES2=sucpssr_distance.cpp

SOURCES3=shuffling_distance.cpp

OBJECTS1=$(SOURCES1:.cpp=.o)

OBJECTS2=$(SOURCES2:.cpp=.o)

OBJECTS3=$(SOURCES3:.cpp=.o)

EXECUTABLE1=$(SOURCES1:.cpp=)

EXECUTABLE2=$(SOURCES2:.cpp=)

EXECUTABLE3=$(SOURCES3:.cpp=)

.cpp.o:
	@echo "---------------------------------------------------------------------------"
	@echo
	$(CPP) $(INCLUDES) $(CFLAGS) -c $< -o $@
	@echo
	@echo "---------------------------------------------------------------------------"
	@echo

all: $(EXECUTABLE1) $(EXECUTABLE2) $(EXECUTABLE3)

$(EXECUTABLE1): $(OBJECTS1)
	@echo "---------------------------------------------------------------------------"
	@echo
	$(CPP) $(INCLUDES) $(CFLAGS) $(OBJECTS1) -o $(EXECUTABLE1) $(LIBRARIES)
	@echo
	@echo "---------------------------------------------------------------------------"
	@echo

$(EXECUTABLE2): $(OBJECTS2)
	@echo "---------------------------------------------------------------------------"
	@echo
	$(CPP) $(INCLUDES) $(CFLAGS) $(OBJECTS2) -o $(EXECUTABLE2) $(LIBRARIES)
	@echo
	@echo "---------------------------------------------------------------------------"
	@echo

$(EXECUTABLE3): $(OBJECTS3)
	@echo "---------------------------------------------------------------------------"
	@echo
	$(CPP) $(INCLUDES) $(CFLAGS) $(OBJECTS3) -o $(EXECUTABLE3) $(LIBRARIES)
	@echo
	@echo "---------------------------------------------------------------------------"
	@echo

clean:
	@echo "Cleaning-up the mess..."
	@rm -f $(OBJECTS1) $(EXECUTABLE1) $(OBJECTS2) $(EXECUTABLE2) $(OBJECTS3) $(EXECUTABLE3) *~
	@echo "Done!"
