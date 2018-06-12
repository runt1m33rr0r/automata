#include "DeterminateFiniteAutomatonInt.h"

DeterminateFiniteAutomatonInt::DeterminateFiniteAutomatonInt()
{
}

DeterminateFiniteAutomatonInt::DeterminateFiniteAutomatonInt(
	const SmartArray<char>& alphabet, const SmartArray<State>& states, TransitionTable & transitionTable)
	: alphabet(alphabet), states(states), transitionTable(transitionTable)
{
}

State & DeterminateFiniteAutomatonInt::getStateByName(const String & name)
{
	for (size_t i = 0; i < this->states.getCount(); i++)
	{
		if (this->states[i].getName() == name)
		{
			return this->states[i];
		}
	}

	throw std::exception("State does not exist!");
}

const State * DeterminateFiniteAutomatonInt::findDanglingState() const
{
	for (size_t row = 0; row < this->transitionTable.getCount(); row++)
	{
		for (size_t col = 0; col < this->transitionTable[row].getCount(); col++)
		{
			int index = this->states.indexOf(this->transitionTable[row][col]);
			if (index < 0)
			{
				return &this->transitionTable[row][col];
			}
		}
	}

	return nullptr;
}

SmartArray<State> DeterminateFiniteAutomatonInt::getFinalStates() const
{
	SmartArray<State> finalStates;
	for (size_t stateIdx = 0; stateIdx < this->states.getCount(); stateIdx++)
	{
		if (this->states[stateIdx].getFinal())
		{
			finalStates.add(this->states[stateIdx]);
		}
	}

	return finalStates;
}

SmartArray<State> DeterminateFiniteAutomatonInt::mergeRows(
	const SmartArray<State>& firstRow, 
	const SmartArray<State>& secondRow,
	MergeMode mode)
{
	SmartArray<State> newRow;

	for (size_t i = 0; i < firstRow.getCount(); i++)
	{
		State first = firstRow[i];
		State second = secondRow[i];
		State merged = DeterminateFiniteAutomatonInt::mergeStates(first, second, mode);

		newRow.add(merged);
	}

	return newRow;
}

State DeterminateFiniteAutomatonInt::mergeStates(const State & first, const State & second, MergeMode mode)
{
	String newStateName = first.getName() + second.getName();
	bool isStarting = first.getStarting() && second.getStarting();
	bool isFinal = false;
	if (mode == MergeMode::Union)
	{
		isFinal = first.getFinal() || second.getFinal();
	}
	else
	{
		isFinal = first.getFinal() && second.getFinal();
	}

	SmartArray<State> composite;
	composite.add(first);
	composite.add(second);

	return State(newStateName, isStarting, isFinal, composite);
}

DeterminateFiniteAutomatonInt DeterminateFiniteAutomatonInt::mergeAutomata(
	const DeterminateFiniteAutomatonInt & first,
	const DeterminateFiniteAutomatonInt & second,
	MergeMode mode)
{
	DeterminateFiniteAutomatonInt newAutomaton;
	newAutomaton.alphabet = first.alphabet;

	State mergedState = DeterminateFiniteAutomatonInt::mergeStates(
		first.getStartingState(),
		second.getStartingState(), mode);
	SmartArray<State> mergedFirstRow = DeterminateFiniteAutomatonInt::mergeRows(
		first.transitionTable[0],
		second.transitionTable[0],
		mode);
	newAutomaton.states.add(mergedState);
	newAutomaton.transitionTable.add(mergedFirstRow);

	const State * danglingState;
	int firstRowIdx;
	int secondRowIdx;
	SmartArray<State> firstRow;
	SmartArray<State> secondRow;
	SmartArray<State> mergedRow;

	do
	{
		danglingState = newAutomaton.findDanglingState();
		if (danglingState != nullptr)
		{
			State firstInner = danglingState->getInnerStates()[0];
			State secondInner = danglingState->getInnerStates()[1];
			firstRowIdx = first.states.indexOf(firstInner);
			secondRowIdx = second.states.indexOf(secondInner);
			firstRow = first.transitionTable[firstRowIdx];
			secondRow = second.transitionTable[secondRowIdx];
			mergedRow = DeterminateFiniteAutomatonInt::mergeRows(firstRow, secondRow, mode);

			newAutomaton.states.add(*danglingState);
			newAutomaton.transitionTable.add(mergedRow);
		}
	} while (danglingState != nullptr);

	return newAutomaton;
}

const State & DeterminateFiniteAutomatonInt::getStartingState() const
{
	for (size_t i = 0; i < this->states.getCount(); i++)
	{
		if (this->states[i].getStarting())
		{
			return this->states[i];
		}
	}

	throw std::exception("State does not exist!");
}

void DeterminateFiniteAutomatonInt::setStartingState(String name)
{
	if (this->getStartingState().getStarting())
	{
		throw std::exception("Automaton already has starting state!");
	}

	this->getStateByName(name).setStarting(true);
}

void DeterminateFiniteAutomatonInt::unsetStartingState()
{
	String startingName = this->getStartingState().getName();
	this->getStateByName(startingName).setStarting(false);
}

void DeterminateFiniteAutomatonInt::setFinalState(String name)
{
	this->getStateByName(name).setFinal(true);
}

bool DeterminateFiniteAutomatonInt::doesRecognizeWord(const String & word) const
{
	State currentState = this->getStartingState();
	size_t currentStateIdx = 0;

	for (size_t letterIdx = 0; letterIdx < word.getLen(); letterIdx++)
	{
		char currentLetter = word[letterIdx];
		size_t letterInAlphabetIdx = this->alphabet.indexOf(currentLetter);
		currentStateIdx = this->states.indexOf(currentState);

		currentState = this->transitionTable[letterInAlphabetIdx][currentStateIdx];
	}

	return currentState.getFinal();
}

DeterminateFiniteAutomatonInt DeterminateFiniteAutomatonInt::operator|(
	const DeterminateFiniteAutomatonInt & other) const
{
	return DeterminateFiniteAutomatonInt::mergeAutomata(*this, other, MergeMode::Union);
}

DeterminateFiniteAutomatonInt DeterminateFiniteAutomatonInt::operator&(
	const DeterminateFiniteAutomatonInt & other) const
{
	return DeterminateFiniteAutomatonInt::mergeAutomata(*this, other, MergeMode::Intersection);
}

DeterminateFiniteAutomatonInt DeterminateFiniteAutomatonInt::operator^(
	const DeterminateFiniteAutomatonInt & other) const
{
	DeterminateFiniteAutomatonInt newAutomaton(other);
	for (size_t i = 0; i < newAutomaton.states.getCount(); i++)
	{
		if (newAutomaton.states[i].getFinal())
		{
			newAutomaton.states[i].setFinal(false);
		}
		else
		{
			newAutomaton.states[i].setFinal(true);
		}
	}

	for (size_t row = 0; row < newAutomaton.transitionTable.getCount(); row++)
	{
		for (size_t col = 0; col < newAutomaton.alphabet.getCount(); col++)
		{
			if (newAutomaton.transitionTable[row][col].getFinal())
			{
				newAutomaton.transitionTable[row][col].setFinal(false);
			}
			else
			{
				newAutomaton.transitionTable[row][col].setFinal(true);
			}
		}
	}

	return newAutomaton;
}

std::ostream & DeterminateFiniteAutomatonInt::insertDataInStream(std::ostream & out) const
{
	out << "  ";
	for (size_t i = 0; i < this->alphabet.getCount(); i++)
	{
		out << "  " << this->alphabet[i];
	}
	out << std::endl;

	for (size_t i = 0; i < this->states.getCount(); i++)
	{
		out << states[i].getName() << " ";
		for (size_t j = 0; j < this->alphabet.getCount(); j++)
		{
			out << (transitionTable[i][j].getStarting() ? "s" : "");
			out << (transitionTable[i][j].getFinal() ? "f" : "");
			out << transitionTable[i][j].getName() << " ";
		}
		out << std::endl;
	}

	return out;
}

std::istream & DeterminateFiniteAutomatonInt::extractDataFromStream(std::istream & in)
{
	unsigned statesCount = 0;
	std::cout << "number of states: ";
	std::cin >> statesCount;

	for (size_t i = 0; i < statesCount; i++)
	{
		String stateName;
		std::cout << "state" << i << " name: ";
		std::cin >> stateName;

		this->states.add(State(stateName));
	}

	unsigned symbolsCount = 0;
	std::cout << "number of symbols: ";
	std::cin >> symbolsCount;

	for (size_t i = 0; i < symbolsCount; i++)
	{
		char symbol;
		std::cout << "symbol" << i << " name: ";
		std::cin >> symbol;

		this->alphabet.add(symbol);
	}

	for (size_t stateIdx = 0; stateIdx < statesCount; stateIdx++)
	{
		SmartArray<State> rowStates;
		for (size_t symbolIdx = 0; symbolIdx < symbolsCount; symbolIdx++)
		{
			std::cout << "transition (" << states[stateIdx].getName() << ", " 
				<< this->alphabet[symbolIdx] << ")->";
			String toName;
			std::cin >> toName;
			rowStates.add(State(toName));
		}

		this->transitionTable.add(rowStates);
	}

	return in;
}

std::ofstream & DeterminateFiniteAutomatonInt::insertDataInFile(std::ofstream & out) const
{
	out << "1" << std::endl;

	// print states
	out << this->states.getCount() << " ";
	for (size_t stateIdx = 0; stateIdx < this->states.getCount(); stateIdx++)
	{
		out << this->states[stateIdx].getName() << " ";
	}
	out << std::endl;

	// print alphabet
	out << this->alphabet.getCount() << " ";
	for (size_t symbolIdx = 0; symbolIdx < this->alphabet.getCount(); symbolIdx++)
	{
		out << this->alphabet[symbolIdx] << " ";
	}
	out << std::endl;

	// print transition table
	for (size_t row = 0; row < this->transitionTable.getCount(); row++)
	{
		for (size_t col = 0; col < this->transitionTable[0].getCount(); col++)
		{
			out << this->transitionTable[row][col].getName() << " ";
		}
		out << std::endl;
	}

	// print starting state
	out << this->getStartingState().getName() << std::endl;

	// print final states
	SmartArray<State> finalStates = this->getFinalStates();
	out << finalStates.getCount() << " ";
	for (size_t stateIdx = 0; stateIdx < finalStates.getCount(); stateIdx++)
	{
		out << finalStates[stateIdx].getName() << " ";
	}

	return out;
}

std::ifstream & DeterminateFiniteAutomatonInt::extractDataFromFile(std::ifstream & in)
{
	unsigned mess;
	in >> mess;

	// read states
	unsigned statesCount = 0;
	String currentStateName;
	in >> statesCount;
	for (size_t i = 0; i < statesCount; i++)
	{
		in >> currentStateName;
		State newState(currentStateName);
		if (this->states.indexOf(newState) < 0)
		{
			this->states.add(State(currentStateName));
		}
	}

	// read alphabet
	unsigned symbolsCount = 0;
	char currentSymbol = ' ';
	in >> symbolsCount;
	for (size_t i = 0; i < symbolsCount; i++)
	{
		in >> currentSymbol;
		if (this->alphabet.indexOf(currentSymbol) < 0)
		{
			this->alphabet.add(currentSymbol);
		}
	}

	// read transition table
	for (size_t row = 0; row < symbolsCount; row++)
	{
		SmartArray<State> currentRow;
		for (size_t col = 0; col < statesCount; col++)
		{
			in >> currentStateName;
			State newState(currentStateName);
			if (transitionTable[row].indexOf(newState) < 0)
			{
				currentRow.add(newState);
			}
		}
		this->transitionTable.add(currentRow);
	}

	// read starting state
	in >> currentStateName;
	this->getStateByName(currentStateName).setStarting(true);
	for (size_t i = 0; i < this->transitionTable.getCount(); i++)
	{
		int index = this->transitionTable[i].indexOf(this->getStateByName(currentStateName));
		if (index > -1)
		{
			this->transitionTable[i][index].setStarting(true);
		}
	}

	// read final states
	unsigned finalStatesCount = 0;
	in >> finalStatesCount;
	for (size_t i = 0; i < finalStatesCount; i++)
	{
		in >> currentStateName;
		this->getStateByName(currentStateName).setFinal(true);

		for (size_t j = 0; j < this->transitionTable.getCount(); j++)
		{
			int index = this->transitionTable[j].indexOf(this->getStateByName(currentStateName));
			if (index > -1)
			{
				this->transitionTable[j][index].setFinal(true);
			}
		}
	}

	return in;
}

std::ostream & operator<<(std::ostream & out, const DeterminateFiniteAutomatonInt & obj)
{
	return obj.insertDataInStream(out);
}

std::istream & operator>>(std::istream & in, DeterminateFiniteAutomatonInt & obj)
{
	return obj.extractDataFromStream(in);
}

std::ofstream & operator<<(std::ofstream & out, const DeterminateFiniteAutomatonInt & obj)
{
	return obj.insertDataInFile(out);
}

std::ifstream & operator>>(std::ifstream & in, DeterminateFiniteAutomatonInt & obj)
{
	return obj.extractDataFromFile(in);
}
