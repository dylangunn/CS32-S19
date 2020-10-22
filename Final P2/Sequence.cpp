#include "Sequence.h"
#include <iostream>

Sequence::Sequence() : m_size(0)
{
	head = new Node;
	head->next = head;
	head->prev = head;
}

Sequence::Sequence(const Sequence& other) : m_size(other.size())			// Copy constructor
{
	head = new Node;			// Initialize
	head->next = head;
	head->prev = head;

	for (Node* p = other.head->next; p != other.head; p = p->next)	// Provide values
	{
		Node* added = new Node;
		added->m_value = p->m_value;
		added->next = head;
		added->prev = head->prev;
		head->prev = added;
		added->prev->next = added;
	}
}

Sequence& Sequence::operator=(const Sequence& other)						// Assignment operator
{
	if (this != &other)
	{
		Sequence temp(other);
		swap(temp);
	}
	return *this;
}

Sequence::~Sequence()														// Destructor
{
	while (head->next != head)
	{
		Node* p = head->next;
		head->next = p->next;
		p->next->prev = p->prev;
		delete p;
	}
	delete head;
}

bool Sequence::empty() const
{
	if (m_size == 0)
		return 1;
	else
		return 0;
}

int Sequence::size() const
{
	return m_size;
}

int Sequence::insert(int pos, const ItemType& value)
{
	if ((pos < 0) || (pos > m_size))
		return -1;
	if (pos >= 0 && pos < m_size)					// Works for empty sequence, insert inside filled sequence
	{
		Node* p = head->next;
		for (int i = 0; i < m_size; i++)
		{
			if (i == pos)
			{
				Node* new_node = new Node;
				new_node->m_value = value;
				new_node->next = p;
				new_node->prev = p->prev;
				p->prev = new_node;
				new_node->prev->next = new_node;
				m_size++;

				return pos;
			}
			p = p->next;
		}
	}
	else if (pos == m_size)							// Insert at end of filled sequence
	{
		Node* new_node = new Node;
		new_node->m_value = value;
		new_node->next = head;
		new_node->prev = head->prev;
		head->prev = new_node;
		new_node->prev->next = new_node;
		m_size++;

		return pos;
	}
	return -1;
}

int Sequence::insert(const ItemType& value)
{
	if (empty())								// Empty
	{
		insert(0, value);

		return 0;
	}

	Node* p = head->next;
	int pos = 0;
	for (int i = 0; i < size(); i++)		// Filled (beginning/middle)
	{
		if (p->m_value >= value)
		{
			pos = i;
			break;
		}
		else
			pos = size();					// Filled (end)
		p = p->next;
	}
	insert(pos, value);

	return pos;
}

bool Sequence::erase(int pos)
{
	if (pos < 0 || pos >= m_size)
		return 0;
	Node* p = head->next;
	for (int i = 0; i < size(); i++)
	{
		if (i == pos)
		{
			p->next->prev = p->prev;
			p->prev->next = p->next;
			delete p;
			m_size--;
			return 1;
		}
		p = p->next;
	}
	return 0;
}

int Sequence::remove(const ItemType& value)
{
	int counter = 0;
	int pos = 0;
	for (Node* p = head->next; p != head; p = p->next)
	{
		if (p->m_value == value)
		{
			p = p->prev;
			erase(pos);				// Problem is here.
			counter++;
		}
		pos++;
	}
	return counter;
}

bool Sequence::get(int pos, ItemType& value) const
{
	if (pos >= 0 && pos < m_size)
	{
		Node* p = head->next;
		for (int i = 0; i < m_size; i++)
		{
			if (i == pos)
			{
				value = p->m_value;
				return 1;
			}
			p = p->next;
		}
	}
	return 0;
}

bool Sequence::set(int pos, const ItemType& value)
{
	if (pos >= 0 && pos < m_size)
	{
		Node* p = head->next;
		for (int i = 0; i < m_size; i++)
		{
			if (i == pos)
			{
				p->m_value = value;
				return 1;
			}
			p = p->next;
		}
	}
	return 0;
}

int Sequence::find(const ItemType& value) const
{
	if (m_size > 0)
	{
		Node* p = head->next;
		for (int i = 0; i < m_size; i++)
		{
			if (value == p->m_value)
			{
				return i;
			}
			p = p->next;
		}
	}
	return -1;

}

void Sequence::swap(Sequence& other)
{
	Node* tempHead = head;					// Swap Heads
	head = other.head;
	other.head = tempHead;

	int tempSize = m_size;					// Swap Sizes
	m_size = other.m_size;
	other.m_size = tempSize;
}

void Sequence::dump() const     // Prints out all the values in the Sequence to cerr for testing purposes.
{
	int counter = 0;
	for (Node* p = head->next; p != head; p = p->next)
	{
		std::cerr << p->m_value << std::endl;
		counter++;
	}
	if (counter != size())
		std::cerr << "==========SIZE MISMATCH============";
}

int subsequence(const Sequence& seq1, const Sequence& seq2)
{
	if (seq2.empty())
		return -1;
	
	ItemType a, b;
	for (int i = 0; i < seq1.size(); i++)
	{
		seq1.get(i, a);
		seq2.get(0, b);
		if ((a == b) && (i + seq2.size() <= seq1.size()))
		{
			for (int j = 1; j < seq2.size(); j++)
			{
				ItemType c, d;
				seq1.get(i + j, c);
				seq2.get(j, d);
				if (c != d)
					break;
				if (j == seq2.size() - 1)
					return i;
			}
		}
	}
	return -1;
}

void interleave(const Sequence& seq1, const Sequence& seq2, Sequence& result)
{
	Sequence tempResult(result);
	while (!tempResult.empty())
		tempResult.erase(0);

	if ((seq1.size() == 0) && (seq2.size() == 0))
		tempResult = seq1;
	if ((seq1.size() != 0) && (seq2.size() == 0))
		tempResult = seq1;
	if ((seq1.size() == 0) && (seq2.size() != 0))
		tempResult = seq2;

	ItemType a, b;
	int i = 0, j = 0, k = 0;
	while (i < seq1.size() || j < seq2.size())	// Go until end of both
	{
		if (i < seq1.size())		// Inserts in order, seq1 then seq2.  If seq1 or seq2 run out, ends up just printing out rest of the other.
		{
			seq1.get(i, a);
			tempResult.insert(k, a);
			i++;
			k++;
		}
		if (j < seq2.size())
		{
			seq2.get(j, b);
			tempResult.insert(k, b);
			j++;
			k++;
		}
	}
	result = tempResult;
}