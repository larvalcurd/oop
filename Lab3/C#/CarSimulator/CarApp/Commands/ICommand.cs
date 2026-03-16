namespace CarApp.Commands;

public interface ICommand
{
    string Name { get; }
    void Execute(Car.Car car, string[] args);
}