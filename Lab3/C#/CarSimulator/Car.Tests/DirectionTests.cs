namespace Car.Tests;

public class DirectionTests
{
    [Test]
    public void Direction_WhenMovingForward_IsForward()
    {
        var car = new Car();
        car.TurnOnEngine();
        car.SetGear(1);
        car.SetSpeed(10);
        Assert.That(car.GetDirection(), Is.EqualTo(Direction.Forward));
    }

    [Test]
    public void Direction_WhenMovingBackward_IsBackward()
    {
        var car = new Car();
        car.TurnOnEngine();
        car.SetGear(-1);
        car.SetSpeed(10);
        Assert.That(car.GetDirection(), Is.EqualTo(Direction.Backward));
    }

    [Test]
    public void Direction_WhenStopped_IsStandingStill()
    {
        var car = new Car();
        car.TurnOnEngine();
        car.SetGear(1);
        car.SetSpeed(10);
        car.SetSpeed(0);
        Assert.That(car.GetDirection(), Is.EqualTo(Direction.StandingStill));
    }

    [Test]
    public void Direction_MovingBackwardOnNeutral_StaysBackward()
    {
        var car = new Car();
        car.TurnOnEngine();
        car.SetGear(-1);
        car.SetSpeed(15);
        car.SetGear(0);
        car.SetSpeed(10);
        Assert.That(car.GetDirection(), Is.EqualTo(Direction.Backward));
        Assert.That(car.GetSpeed(), Is.EqualTo(10));
    }
}
