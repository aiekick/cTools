# cTools

a two files helper im using from more than 10 years, in all my project.

Contain usefull templated things for c++ like vec2, vec3, vec4, variant, actionTime and more.

need a bit of refactoring btw :)

use the namespace ct

## Class :

- ct::cCyclicArray => circular list
- ct::cActionTime => define when to do action accroding to time of last event
- ct::cTexture => opengl texture simple container
- ct::cColor => color class for conversion
- ct::vec2<T> => vec2 class for quick operation / math x,y
- ct::mat2<T> => mat2 class for matrix 2x2
- ct::vec3<T> => vec3 class for quick operation / math x,y,z
- ct::vec4<T> => vec4 class for quick operation / math x,y,z,z
- ct::rect<T> => rect class for quick operation / math x,y,w,h
- ct::AABB<T> => AABB 2D
- ct::AABBCC<T> => AABB 3D
- ct::variant<T> => variant class for quikc conversion between many type and string

and other string conversion / extraction etc..
