namespace TVSetApp.Commands;

public interface ICommand
{
    string Name { get; }
    void Execute(TVSet tv, string[] args);
}