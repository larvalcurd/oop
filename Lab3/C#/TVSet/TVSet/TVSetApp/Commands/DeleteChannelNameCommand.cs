using System.Windows.Input;

namespace TVSetApp.Commands;

public class DeleteChannelNameCommand : ICommand
{
    public string Name => "DeleteChannelName";

    public void Execute(TVSet tv, string[] args)
    {
        if (args.Length < 1)
        {
            Console.WriteLine("ERROR");
            return;
        }



        string channelName = string.Join(" ", args);


        if (tv.DeleteChannelName(channelName))
        {
            Console.WriteLine($"Channel name deleted: {channelName}");
        }
        else
        {
            Console.WriteLine("ERROR");
        }
    }
}