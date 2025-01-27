struct GateSequencer : Sequencer
{
    // std::array<bool, MAX_SEQUENCER_STEPS> sequence;

    std::vector<bool> sequence;

    // constructor
    GateSequencer()
    {
    }

    // This must be called before interacting with the voltage sequencer since
    // it sets the size of the vector and initializes it with "value"
    void assign(unsigned int length, double value)
    {
        sequence.assign(length, value);
    }

    bool getValue(int index)
    {
        return (sequence[index]);
    }

    bool getValue()
    {
        return (sequence[sequence_playback_position]);
    }

    void setValue(int index, bool value)
    {
        sequence[index] = value;
    }

    void shiftLeft()
    {
        double temp = sequence[0];
        for (unsigned int i = 0; i < this->sequence_length - 1; i++)
        {
            sequence[i] = sequence[i + 1];
        }
        sequence[this->sequence_length - 1] = temp;
    }

    void shiftRight()
    {
        double temp = sequence[this->sequence_length - 1];

        for (unsigned int i = this->sequence_length - 1; i > 0; i--)
        {
            sequence[i] = sequence[i - 1];
        }

        sequence[0] = temp;
    }

    void randomize()
    {
        for (unsigned int i = 0; i < this->sequence_length; i++)
        {
            this->setValue(i, fmod(std::rand(), 2));
        }
    }

    void clear()
    {
        // sequence.fill(0.0);
        sequence.assign(sequence.size(), 0);
    }
};