namespace CarApp.Commands;

public class SetGearCommand : ICommand
{
    public string Name => "SetGear";

    public void Execute(Car.Car car, string[] args)
    {
        if (args.Length < 1 || !int.TryParse(args[0], out int gear))
        {
            Console.WriteLine("Invalid command argument");
            return;
        }

        if (gear < -1 || gear > 5)
        {
            Console.WriteLine("Invalid gear");
            return;
        }

        if (!car.IsTurnedOn && gear != 0)
        {
            Console.WriteLine("Cannot set gear while engine is off");
            return;
        }

        if (gear == -1 && car.GetSpeed() != 0)
        {
            Console.WriteLine("Cannot reverse while moving");
            return;
        }

        if (gear > 0 && car.GetDirection() == Car.Direction.Backward)
        {
            Console.WriteLine("Cannot reverse while moving");
            return;
        }

        if (!car.SetGear(gear))
        {
            Console.WriteLine("Unsuitable current speed");
            return;
        }
    }
}