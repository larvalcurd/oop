namespace TVSetApp.Commands;

public class TurnOffCommand : ICommand
{
    public string Name => "TurnOff";

    public void Execute(TVSet tv, string[] args)
    {
        tv.TurnOff();
        Console.WriteLine("TV is turned off");
    }
}