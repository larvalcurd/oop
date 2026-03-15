namespace TVSetApp.Commands;

public class SelectPreviousChannelCommand : ICommand
{
    public string Name => "SelectPreviousChannel";

    public void Execute(TVSet tv, string[] args)
    {
        int OldChannel = tv.GetChannel();
        tv.SelectPreviousChannel();

        if (tv.GetChannel() != OldChannel)
        {
            Console.WriteLine($"Switched to previous channel");
        }
        else
        {
            Console.WriteLine("ERROR");
        }
    }
}