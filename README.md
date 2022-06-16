# Movement along curves with constant velocity

The ducks will move along curves with equations:
$$ f(x) = A \times sin{bx} $$
$$ f'(x) = A * b * cos{bx} $$

Given the current position, delta time and velocity, I want to be able to calculate the next position, ensuring constant velocity.
The length of a polynomial curve is:
$$ \int_{a}^{b} sqrt{ 1 + [f'(x)^2]}dx $$

$$ \int_{a}^{b} sqrt{ 1 + A*b*cos(b*x)^2} dx$$

The value of the integral will be estimated using the trapeziod rule.


# Resources

1) [Duck texture](https://opengameart.org/content/character-spritesheet-duck)
2) [Egg](https://opengameart.org/content/egg-item-sprite)
3) [Spaceship](https://opengameart.org/content/spaceship-1)
4) [Projectiles](https://opengameart.org/content/pure-projectile-magic-effect)
5) [Store](https://www.flaticon.com/free-icons/shop)