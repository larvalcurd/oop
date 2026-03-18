namespace Car.Tests;

public class SpeedTests
{
    [Test]
    public void SetSpeed_EngineOff_ReturnsFalse()
    {
        var car = new Car();
        bool result = car.SetSpeed(10);
        Assert.That(result, Is.False);
    }

    [Test]
    public void SetSpeed_NegativeSpeed_ReturnsFalse()
    {
        var car = new Car();
        car.TurnOnEngine();
        car.SetGear(1);
        bool result = car.SetSpeed(-10);
        Assert.That(result, Is.False);
    }

    [Test]
    public void SetSpeed_InGearRange_ReturnsTrue()
    {
        var car = new Car();
        car.TurnOnEngine();
        car.SetGear(1);
        bool result = car.SetSpeed(15);
        Assert.That(result, Is.True);
        Assert.That(car.GetSpeed(), Is.EqualTo(15));
    }

    [Test]
    public void SetSpeed_OutOfGearRange_ReturnsFalse()
    {
        var car = new Car();
        car.TurnOnEngine();
        car.SetGear(1);
        bool result = car.SetSpeed(50);
        Assert.That(result, Is.False);
        Assert.That(car.GetSpeed(), Is.EqualTo(0));
    }

    [Test]
    public void SetSpeed_OnNeutral_CanDecelerate()
    {
        var car = new Car();
        car.TurnOnEngine();
        car.SetGear(1);
        car.SetSpeed(20);
        car.SetGear(0);
        bool result = car.SetSpeed(10);
        Assert.That(result, Is.True);
        Assert.That(car.GetSpeed(), Is.EqualTo(10));
    }

    [Test]
    public void SetSpeed_OnNeutral_CannotAccelerate()
    {
        var car = new Car();
        car.TurnOnEngine();
        car.SetGear(1);
        car.SetSpeed(20);
        car.SetGear(0);
        bool result = car.SetSpeed(25);
        Assert.That(result, Is.False);
        Assert.That(car.GetSpeed(), Is.EqualTo(20));
    }
}
