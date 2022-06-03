# Credit

Program that determines whether a provided credit card number is valid according to Luhn’s algorithm.

## Usage

Run the following commands in order to compile this program:

```bash
$ make credit
```

Execute program

```bash
$ python credit.py
Number: 378282246310005
AMEX
```

Test other examples

```bash
$ python credit.py
Number: 371449635398431
AMEX
```

```bash
$ python credit.py
Number: 5555555555554444
MASTERCARD
```

```bash
$ python credit.py
Number: 5555555555554444
MASTERCARD
```

```bash
$ python credit.py
Number: 4111111111111111
VISA
```

```bash
$ python credit.py
Number: 4012888888881881
VISA
```

```bash
$ python credit.py
Number: 1234567890
INVALID
```
