namespace TVSetApp;

public class TVSet
{
    private int _currentChannel = 0;
    private int _previousChannel = 0;

    private Dictionary<int, string> _channelToName = new();
    private Dictionary<string, int> _nameToChannel = new();
    public bool IsOn { get; private set; }

    public IEnumerable<(int Channel, string Name)> GetAllChannelNames()
    {
        return _channelToName
            .OrderBy(x => x.Key)
            .Select(x => (x.Key, x.Value));
    }

    public void TurnOn()
    {
        IsOn = true;
        if (_currentChannel == 0)
        {
            _currentChannel = 1;
        }
    }

    public void TurnOff()
    {
        IsOn = false;
    }

    public int GetChannel()
    {
        return IsOn ? _currentChannel : 0;
    }

    public void SelectChannel(int channel)
    {
        if (IsOn && channel > 0 && channel <= 99)
        {
            _previousChannel = _currentChannel;
            _currentChannel = channel;
        }
    }

    public void SelectChannel(string name)
    {
        int channel = GetChannelByName(name);
        if (channel != 0)
        {
            SelectChannel(channel);
        }
    }

    public void SelectPreviousChannel()
    {
        if (IsOn && _previousChannel != 0)
        {
            int temp = _currentChannel;
            _currentChannel = _previousChannel;
            _previousChannel = temp;
        }
    }

    public string? GetChannelName(int channel)
    {
        return _channelToName.TryGetValue(channel, out string? name) ? name : null;
    }

    public int GetChannelByName(string name)
    {
        return _nameToChannel.TryGetValue(name, out int channel) ? channel : 0;
    }

    public bool SetChannelName(int channel, string name)
    {
        if (!IsOn)
        {
            return false;
        }

        if (channel <= 0 || channel > 99)
        {
            return false;
        }

        name = name.Trim();

        if (string.IsNullOrWhiteSpace(name))
        {
            return false;
        }

        if (_nameToChannel.TryGetValue(name, out int oldChannel))
        {
            _channelToName.Remove(oldChannel);
        }

        if (_channelToName.TryGetValue(channel, out string? oldName))
        {
            _nameToChannel.Remove(oldName);
        }

        _channelToName[channel] = name;
        _nameToChannel[name] = channel;

        return true;
    }

    public bool DeleteChannelName(string name)
    {
        if (!IsOn)
        {
            return false;
        }

        name = name.Trim();

        if (!_nameToChannel.TryGetValue(name, out int channel))
        {
            return false;
        }

        _nameToChannel.Remove(name);
        _channelToName.Remove(channel);

        return true;
    }
}
