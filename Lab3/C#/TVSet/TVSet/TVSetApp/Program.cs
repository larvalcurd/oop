using TVSetApp;

var handler = new CommandHandler();

while (Console.ReadLine() is string input)
{
    handler.HandleCommand(input);
}
