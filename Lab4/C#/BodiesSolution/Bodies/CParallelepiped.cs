namespace Bodies;

public class CParallelepiped : CSolidBody
{
    private readonly double _width;
    private readonly double _height;
    private readonly double _depth;

    public CParallelepiped(double density, double width, double height, double depth) : base(density)
    {
        if (width <= 0)
        {
            throw new ArgumentException("Width must be positive", nameof(width));
        }

        if (height <= 0)
        {
            throw new ArgumentException("Height must be positive", nameof(height));
        }

        if (depth <= 0)
        {
            throw new ArgumentException("Depth must be positive", nameof(depth));
        }

        _width = width;
        _height = height;
        _depth = depth;
    }

    public double GetWidth()
    {
        return _width;
    }

    public double GetHeight()
    {
        return _height;
    }

    public double GetDepth()
    {
        return _depth;
    }

    public override double GetVolume()
    {
        return _width * _height * _depth;
    }

    public override string ToString()
    {
        return $"Parallelepiped: Width = {_width:F3}, Height = {_height:F3}, Depth = {_depth:F3}, {base.ToString()}";
    }
}