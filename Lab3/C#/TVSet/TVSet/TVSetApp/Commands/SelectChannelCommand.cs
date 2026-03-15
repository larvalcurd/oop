namespace TVSetApp.Commands;

public class SelectChannelCommand : ICommand
{
    public string Name => "SelectChannel";

    public void Execute(TVSet tv, string[] args)
    {
        if (args.Length < 1)
        {
            Console.WriteLine("ERROR");
            return;
        }

        int oldChannel = tv.GetChannel();
        bool switched = false;

        if (int.TryParse(args[0], out int channel))
        {
            tv.SelectChannel(channel);
            switched = tv.GetChannel() != oldChannel;
        }
        else
        {
            string name = args[0];
            int channelByName = tv.GetChannelByName(name);
            if (channelByName != 0)
            {
                tv.SelectChannel(name);
                switched = tv.GetChannel() != oldChannel;
            }
        }

        if (switched)
        {
            Console.WriteLine($"Channel switched to: {tv.GetChannel()}");
        }
        else
        {
            Console.WriteLine("ERROR");
        }
    }
}