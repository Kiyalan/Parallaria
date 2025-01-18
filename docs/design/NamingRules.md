
### Type (class struct enum)
- be in PascalCase
- prefixes:
  - F fundamental types
  - T template types
  - E enum class

### Variable

- Be descriptive
- Be in camelCase
- Private member variable, use '_' prefix
- Boolean variable, use 'b' prefix
- Container variable, use container name suffix, e.g. 'Array', 'Map'
- Enum variable, use 'State' suffix

### Function

- Be descriptive
- Be in PascalCase

### Macro

- FULL_CAPPITALED with underscore to separate words
- header re-inclusion prevention macro name, layer prefix + filename + 'INCLUDED', e.g. ENGINE_WINDOW_INCLUDED

### Namespace

- Core Engine Layer use `namespace Engine`

