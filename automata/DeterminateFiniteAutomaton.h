#ifndef DFA
#define DFA

#include <fstream>

#include "SmartArray.h"
#include "State.h"
#include "AutomatonException.h"
#include "AutomatonStateException.h"

enum MergeMode { Union, Intersection };

typedef SmartArray<SmartArray<State>> TransitionTable;

template <typename T>
class DeterminateFiniteAutomaton
{
private:
	SmartArray<T> alphabet;
	SmartArray<State> states;
	TransitionTable transitionTable;

	State & getStateByName(const String & name)
	{
		for (size_t i = 0; i < this->states.getCount(); i++)
		{
			if (this->states[i].getName() == name)
			{
				return this->states[i];
			}
		}

		throw AutomatonStateException(name, __LINE__);
	}

	const State * findDanglingState() const
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

	SmartArray<State> getFinalStates() const
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

	static SmartArray<State> mergeRows(
		const SmartArray<State> & firstRow,
		const SmartArray<State> & secondRow,
		MergeMode mode)
	{
		SmartArray<State> newRow;

		for (size_t i = 0; i < firstRow.getCount(); i++)
		{
			State first = firstRow[i];
			State second = secondRow[i];
			State merged = DeterminateFiniteAutomaton<T>::mergeStates(first, second, mode);

			newRow.add(merged);
		}

		return newRow;
	}

	static State mergeStates(const State & first, const State & second, MergeMode mode)
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

	static DeterminateFiniteAutomaton<T> mergeAutomata(
		const DeterminateFiniteAutomaton<T> & first,
		const DeterminateFiniteAutomaton <T>& second,
		MergeMode mode)
	{
		DeterminateFiniteAutomaton<T> newAutomaton;
		newAutomaton.alphabet = first.alphabet;

		State mergedState = DeterminateFiniteAutomaton<T>::mergeStates(
			*first.getStartingState(),
			*second.getStartingState(), mode);
		SmartArray<State> mergedFirstRow = DeterminateFiniteAutomaton<T>::mergeRows(
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
				mergedRow = DeterminateFiniteAutomaton<T>::mergeRows(firstRow, secondRow, mode);

				newAutomaton.states.add(*danglingState);
				newAutomaton.transitionTable.add(mergedRow);
			}
		} while (danglingState != nullptr);

		return newAutomaton;
	}

public:
	DeterminateFiniteAutomaton<T>()
	{
	}

	DeterminateFiniteAutomaton<T>(
		const SmartArray<T> & alphabet,
		const SmartArray<State>& states,
		const TransitionTable & transitionTable)
		: alphabet(alphabet), states(states), transitionTable(transitionTable)
	{
	}

	const State * getStartingState() const
	{
		for (size_t i = 0; i < this->states.getCount(); i++)
		{
			if (this->states[i].getStarting())
			{
				return &this->states[i];
			}
		}

		return nullptr;
	}

	void setStartingState(String name)
	{
		const State * starting = this->getStartingState();
		if (starting)
		{
			throw AutomatonException(name, starting->getName(), __LINE__);
		}

		this->getStateByName(name).setStarting(true);
	}

	void unsetStartingState()
	{
		this->getStartingState().setStarting(false);
	}

	void setFinalState(String name)
	{
		this->getStateByName(name).setFinal(true);
	}

	bool doesRecognizeWord(const String & word) const
	{
		State currentState = this->getStartingState();
		size_t currentStateIdx = 0;

		for (size_t letterIdx = 0; letterIdx < word.getLen(); letterIdx++)
		{
			T currentLetter = word[letterIdx];
			size_t letterInAlphabetIdx = this->alphabet.indexOf(currentLetter);
			currentStateIdx = this->states.indexOf(currentState);

			currentState = this->transitionTable[letterInAlphabetIdx][currentStateIdx];
		}

		return currentState.getFinal();
	}

	DeterminateFiniteAutomaton<T> operator|(const DeterminateFiniteAutomaton<T> & other) const
	{
		return DeterminateFiniteAutomaton<T>::mergeAutomata(*this, other, MergeMode::Union);
	};

	DeterminateFiniteAutomaton<T> operator&(const DeterminateFiniteAutomaton<T> & other) const
	{
		return DeterminateFiniteAutomaton<T>::mergeAutomata(*this, other, MergeMode::Intersection);
	}

	DeterminateFiniteAutomaton<T> operator^(const DeterminateFiniteAutomaton<T> & other) const
	{
		DeterminateFiniteAutomaton<T> newAutomaton(other);
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

	virtual std::ostream & insertDataInStream(std::ostream & out) const
	{
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
		if (this->getStartingState() != nullptr)
		{
			out << this->getStartingState()->getName() << std::endl;
		}

		// print final states
		SmartArray<State> finalStates = this->getFinalStates();
		out << finalStates.getCount() << " ";
		for (size_t stateIdx = 0; stateIdx < finalStates.getCount(); stateIdx++)
		{
			out << finalStates[stateIdx].getName() << " ";
		}

		return out;
	}

	virtual std::istream & extractDataFromStream(std::istream & in)
	{
		unsigned statesCount = 0;
		std::cout << "number of states: ";
		std::cin >> statesCount;

		for (size_t i = 0; i < statesCount; i++)
		{
			String stateName;
			std::cout << "state [" << i << "]: ";
			std::cin >> stateName;
			this->states.add(State(stateName));
		}

		unsigned symbolsCount = 0;
		std::cout << "number of symbols: ";
		std::cin >> symbolsCount;

		for (size_t i = 0; i < symbolsCount; i++)
		{
			T symbol;
			std::cout << "symbol [" << i << "]: ";
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

		String startingName;
		std::cout << "starting state: ";
		std::cin >> startingName;
		this->setStartingState(startingName);

		unsigned finalStatesCount = 0;
		cout << "final states count: ";
		cin >> finalStatesCount;
		for (size_t i = 1; i <= finalStatesCount; i++)
		{
			std::cout << "final state [" << i << "]: ";
			String finalName;
			cin >> finalName;
			this->getStateByName(finalName).setFinal(true);
		}

		return in;
	}

	virtual std::ifstream & extractDataFromFile(std::ifstream & in)
	{
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
		T currentSymbol;
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
		for (size_t row = 0; row < statesCount; row++)
		{
			in >> currentStateName;
			State newState(currentStateName);

			if (transitionTable[row].indexOf(newState) < 0)
			{
				transitionTable[row].add(newState);
			}
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
};

template <typename T>
std::ostream & operator<<(std::ostream & out, const DeterminateFiniteAutomaton<T> & obj)
{
	if (typeid(obj) == typeid(DeterminateFiniteAutomaton<int>))
	{
		out << "1" << std::endl;
	}
	else if (typeid(obj) == typeid(DeterminateFiniteAutomaton<char>))
	{
		out << "2" << std::endl;
	}
	return obj.insertDataInStream(out);
}

template <typename T>
std::istream & operator>>(std::istream & in, DeterminateFiniteAutomaton<T> & obj)
{
	return obj.extractDataFromStream(in);
}

template <typename T>
std::ifstream & operator>>(std::ifstream & in, DeterminateFiniteAutomaton<T> & obj)
{
	return obj.extractDataFromFile(in);
}

#endif