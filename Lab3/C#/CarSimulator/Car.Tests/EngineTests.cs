namespace Car.Tests;

public class EngineTests
{
    [Test]
    public void TurnOnEngine_WhenEngineIsOff_ReturnsTrue()
    {
        var car = new Car();
        bool result = car.TurnOnEngine();
        Assert.That(result, Is.True);
        Assert.That(car.IsTurnedOn, Is.True);
    }

    [Test]
    public void TurnOnEngine_WhenEngineIsAlreadyOn_ReturnsTrue()
    {
        var car = new Car();
        car.TurnOnEngine();
        bool result = car.TurnOnEngine();
        Assert.That(result, Is.True);
    }

    [Test]
    public void TurnOffEngine_WhenOnAndNeutralAndStopped_ReturnsTrue()
    {
        var car = new Car();
        car.TurnOnEngine();
        bool result = car.TurnOffEngine();
        Assert.That(result, Is.True);
        Assert.That(car.IsTurnedOn, Is.False);
    }

    [Test]
    public void TurnOffEngine_WhenAlreadyOff_ReturnsTrue()
    {
        var car = new Car();
        bool result = car.TurnOffEngine();
        Assert.That(result, Is.True);
    }

    [Test]
    public void TurnOffEngine_WhenNotInNeutral_ReturnsFalse()
    {
        var car = new Car();
        car.TurnOnEngine();
        car.SetGear(1);

        bool result = car.TurnOffEngine();

        Assert.That(result, Is.False);
    }

    [Test]
    public void Example4_CannotTurnOffWhileMoving()
    {
        var car = new Car();
        car.TurnOnEngine();
        car.SetGear(1);
        car.SetSpeed(10);
        bool result = car.TurnOffEngine();
        Assert.That(result, Is.False);
        Assert.That(car.IsTurnedOn, Is.True);
    }
}
