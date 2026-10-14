# Testing

## Table of Contents
| Test | Expected Result | Actual Result | Evidence |
|------|-----------------|---------------|----------|
| No inputs | Print usage of Application | PASS| [View Test](#no-inputs) |
| Wrong Mode | Print an error message | PASS | [View Test](#wrong-mode) |
| Wrong File Location | Print an error message | PASS | [View Test](#wrong-file-location) |
| Wrong Image Type | Print an error message | PASS | [View Test](#wrong-file-type) |
| Empty Text File | Print an error message | PASS | [View Test](#empty-text-file)|
| Word to be encoded is larger than allocated space in PNG | Print an error message | PASS | [View Test](#word-to-be-encoded-is-larger-than-allocated-space-in-png) |
| Key and Clear Text are not the same size | Print an error message | PASS | [View Test](#key-and-clear-text-are-not-the-same-size)|
| Encode RGBA PNG | Produces output.png with encoded message. Prints out encoded value. Image is indistinguishable. | PASS | [View Test](#encode-rgba-png)|
| Decode RGBA PNG | Prints out the encoded message in the output.png | PASS | [View Test](#decode-rgba-png)|
| Encode RGB PNG (all white) | Produces output.png with encoded message. Prints out encoded value. Image is indistinguishable. | PASS | [View Test](#encode-rgb-png-all-white)|
| Decode RGB PNG (all white) | Prints out the encoded message in the output.png | PASS | [View Test](#decode-rgb-png-all-white)|
| Encode RGB PNG (all black) | Produces output.png with encoded message. Prints out encoded value. Image is indistinguishable. | PASS | [View Test](#encode-rgb-png-all-black)|
| Decode RGB PNG (all black) | Prints out the encoded message in the output.png | PASS | [View Test](#decode-rgb-png-all-black)|
| Encode 16 bit PNG | Produces output.png with encoded message. Prints out encoded value. Image is indistinguishable. | FAIL |[View Test](#encode-16-bit-png)|
| Encode GrayScale PNG | Produces output.png with encoded message. Prints out encoded value. Image is indistinguishable. | FAIL | [View Test]|


## No inputs
### Command to replicate
`./app`

![no_input](./no_input.gif)

## Wrong mode
### Command to replicate
`./app`

![wrong_mode](./wrong_input.gif)

## Wrong File Location
### Command to replicate
`./app`

![wrong_file_location](./wrong_file_location.gif)

## Wrong Image Type
### Command to replicate
`./app`

![wrong_file_type](./wrong_file_type.gif)

## Empty Text File
### Command to replicate
`./app`

![empty_text_file](./empty_text.gif)

## Word to be encoded is larger than allocated space in PNG
### Command to replicate
`./app`

![larger_than_png](./larger_than_png.gif)

## Key and Clear Text are not the same size
### Command to replicate
`./app`

![key_clear_not_same_size](./key_clear_not_same_size.gif)

## Encode RGBA PNG
### Command to replicate
`./app`

![encode_rgba_png](./rgba-e.png)

## Decode RGBA PNG
### Command to replicate
`./app`

![decode_rgba_png](./rgba-d.png)

## Encode RGB PNG (all white)
### Command to replicate
`./app`

![encode_white](./white-e.png)

## Decode RGB PNG (all white)
### Command to replicate
`./app`

![decode_white](./white-d.png)

## Encode RGB PNG (all black)
### Command to replicate
`./app`

![encode_black](./black-e.png)

## Decode RGB PNG (all black)
### Command to replicate
`./app`

![decode_black](./black-d.png)

## Encode 16 bit PNG
### Command to replicate
`./app`

![encode_16bit](16bit.png)

## Encode GrayScale PNG
