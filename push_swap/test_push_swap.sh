#!/bin/bash

# Define color codes
RED='\033[0;31m'
GREEN='\033[0;32m'
NC='\033[0m' # No Color

# Define an array of test arguments
ARGS_ERROR=(
	""
	"  "
	"hello world"
	"5 4 a 7"
	"- 9 76"
	"1 2 56 3 '56 765'"
	"-2147483649"
	"1 0 2147483649"
	"7 0 8 -"
	"54m 76 0 9 "
	"1 2 3 4 5 6 7 8 9 1"
)

ARGS=(
	"42"
	"89 4"
	# 3 random values
	"3 2 1"
	"0 2 1"
	"4 6 2147483647"
	# 5 random values
	"1 5 2 4 3  "
	"10 5 8 7 3"
	"-13 241 322 49 37"
	"-0000001 000000002 -00003 001 03"
	"1 2 3 4 5 6 7 8 9" # already sorted
	# 10 random values
	"-21 303 -293 -156 -179 272 -4 354 69 -246"
	# 100 random values
	"311 -286 274 81 -285 210 -15 260 -168 -222 -443 418 451 250 -412 431 183 78 52 189 -43 -88 230 -287 -6 -256 104 66 -9 340 133 -483 498 -231 9 -337 -218 -490 -155 280 -243 -248 440 367 332 -357 32 -493 380 59 187 225 467 425 18 167 445 -10 -396 -22 218 -313 233 -235 56 -131 215 -381 -491 448 84 -97 420 -251 76 -304 -371 356 314 -500 -484 -364 -257 -39 494 -367 -205 169 62 -62 -4 -362 162 -333 441 388 -495 -159 -265 320"
	"403 497 -459 89 -177 421 -167 493 -221 -466 -85 -479 -257 -69 145 299 307 314 -9 -144 -276 -447 424 -482 137 446 316 -11 -40 412 405 -256 256 473 -362 -151 -475 107 -53 -195 94 305 272 -477 -188 112 -14 383 -75 -128 -356 461 -412 379 53 280 -154 352 -413 -201 121 437 221 -107 413 262 65 36 -441 368 -133 -83 -108 294 369 -200 -185 -120 350 -268 -64 -365 -424 332 353 -166 56 -160 -47 243 86 432 -425 -312 109 -333 -456 -65 -110 300"
	# 500 random values
	"109 163 -20 -212 -143 466 -333 487 154 401 -286 -209 -14 231 -273 186 -217 -128 -363 -207 -359 -378 294 382 402 77 -367 -210 17 -315 -352 -419 101 -90 -64 222 -244 267 -6 -465 431 211 361 123 -382 -25 448 -46 246 387 16 -26 -120 -399 -125 236 100 -301 -221 -233 -294 287 -56 232 -133 261 32 -29 49 404 -48 339 177 -117 -191 -393 -255 210 496 93 -257 1 -457 -266 444 413 -185 -421 -467 -329 -276 -418 -28 111 -481 -213 418 12 -365 -136 -162 -47 205 22 -50 202 371 244 -169 -75 253 486 437 -243 348 162 -471 -405 283 -183 135 -61 -70 26 -93 -77 -284 -230 -358 -398 494 254 -472 -480 68 389 -40 150 37 -140 370 -253 74 87 -23 -231 -434 -374 53 329 -216 -431 271 -172 226 133 -478 316 171 -108 -328 62 -206 -74 426 -342 315 -482 -450 365 -302 -406 225 -338 156 120 -88 427 259 351 471 478 -97 -79 264 -239 -13 -403 245 380 324 455 334 -354 -205 -426 -500 481 -37 276 -167 -355 468 312 340 42 -295 326 -287 495 -320 137 -63 -114 8 263 306 173 -59 169 -391 309 -164 -305 -313 454 479 81 223 385 -409 -100 50 103 2 -192 -96 433 -458 215 -62 146 360 -288 -218 139 392 482 66 -81 -168 -86 -228 -337 354 -234 -317 353 -245 -351 -227 352 185 124 -477 266 -115 337 -410 255 -223 69 197 -331 94 441 -460 200 321 -87 -256 327 228 -441 341 407 269 331 192 216 -483 285 214 484 -193 -84 114 -455 -404 -281 -299 -153 461 423 -445 -5 -442 -155 305 -454 -110 -425 105 -45 446 -187 9 -449 -18 -36 -356 238 378 -360 3 -350 -408 -307 -174 -214 -254 464 86 -300 -303 -130 158 -453 -194 406 179 -479 -44 -159 122 -82 313 -375 -423 -42 89 -188 -268 -387 121 -252 126 -436 -180 -496 459 -278 -177 51 117 -416 82 -184 403 136 430 -101 400 -429 -157 -422 153 408 248 129 -371 279 110 91 -325 -304 -310 -324 322 458 -314 300 -397 278 -444 317 274 493 -166 492 46 -11 -95 116 -55 -369 -343 -67 78 159 319 -132 -344 39 -237 286 -264 -400 35 73 -7 30 -102 -361 -452 -2 483 33 -60 -490 -484 332 189 310 -390 268 241 -474 475 -49 -411 34 -85 359 -347 436 500 -446 349 275 -186 56 -38 323 344 -466 289 -250 213 -383 -66 -16 258 -109 59 429 345 399 43 -211 409 161 368 -165 -473 -464 -267 -407 398 -39 -129 415 432 -160 -229 199 167 14 -311 -151 -339 362 -92 272 -486 -381 229 -318 65 440"
	"134 -150 -131 301 -114 186 -259 305 212 -368 -284 416 412 94 34 445 -181 266 -17 251 -354 235 260 1 410 -207 -121 -325 -376 30 220 -336 324 379 243 429 -143 424 -35 380 433 -408 64 6 432 39 369 117 321 479 422 222 -234 296 -382 219 83 406 -327 128 -134 -95 -346 -175 173 415 31 57 116 176 -394 -89 469 -266 -290 -419 -450 -201 -226 -260 27 184 458 105 85 -489 249 -396 -472 -459 225 -54 306 165 323 221 107 50 -205 15 375 -359 -269 -172 223 430 36 20 -13 -191 49 362 304 -70 -53 -196 -23 310 -128 349 474 475 276 -387 -236 -274 -464 -240 -337 -302 101 -148 -105 451 -97 143 404 208 -433 -100 -164 61 86 -378 28 -246 414 254 21 -237 342 152 -238 35 -214 88 393 161 496 -494 499 -361 92 -4 -51 297 -245 4 354 47 33 253 -146 -36 -313 244 110 133 -471 300 166 421 -217 -295 -319 387 -316 138 197 -55 224 -251 371 -402 291 411 13 -426 339 -386 302 -163 -225 23 -492 313 -478 442 189 335 -400 17 -277 -102 111 -161 149 -209 -107 -250 72 471 316 163 167 360 257 -123 -405 345 264 169 436 428 52 -311 209 353 -399 289 -241 58 -3 465 -125 -372 132 -173 -317 -41 -390 140 -78 467 -436 -482 -29 361 399 -407 346 -322 56 -202 398 -180 470 493 -42 115 -16 -496 114 7 -204 452 420 -395 0 -357 -460 -87 364 -315 -11 292 -20 210 261 -9 -362 341 -294 -84 -249 -454 -417 179 38 182 -491 356 391 -168 135 -132 32 95 -80 68 -216 -484 44 -392 382 -222 -193 456 441 -305 -189 -215 464 -119 -192 337 -469 -77 -330 -239 325 -352 -379 198 -155 -49 -66 -272 -19 462 -403 195 450 500 155 482 275 -495 89 431 -381 248 478 -167 112 476 233 -24 376 -162 303 -448 319 338 372 366 395 234 -65 -309 99 -287 144 492 -186 108 -341 141 10 -367 78 -61 443 -104 437 76 438 -154 294 258 287 215 -384 84 204 -481 -424 -213 187 -233 288 -455 272 -210 164 207 -262 -415 214 -57 -109 -318 -73 -434 388 284 37 -112 314 5 80 -46 -110 -328 -440 16 401 -218 419 340 131 -446 -171 487 67 343 -230 439 -439 423 -68 -298 472 -500 334 -98 -176 389 290 468 -47 216 185 45 483 -393 18 11 -347 60 -21 -198 8 -461 81 218 -456 -14 373 -136 -350 -258 -282 154 -117 -12 344 -414 -273 -267 69 409 -371 22 245 247 -261 -108 336 -397 14 -364 -169 -467 -355 65 127 129 -353 480"
)


echo "Running tests with error arguments:"
echo "-----------------------------------"

# Iterate over each test argument
for ARG in "${ARGS_ERROR[@]}"; do

	# Run push_swap and capture the output
	output=$(valgrind ./push_swap "$ARG" 2>&1 | tr -d '\0')


	# Check if the output is equal to "Error"
	if [[ "$output" == "Error" ]];  then
		echo -e "${GREEN}OK: produced correct error output"
		echo -e "${NC}Argument '$ARG' ${NC}"
	else
		echo -e "${RED}Test failed: Argument '$ARG' did not produce error output${NC}"
		echo "Actual output:"
		echo "$output"
	fi
	echo "-----------------------------"

done

echo "-----------------------------------"
echo "Running tests without error arguments:"
echo "-----------------------------------"

# Iterate over each test argument
for ARG in "${ARGS[@]}"; do
	# Run push_swap and pipe the output to checker
	output=$(valgrind ./push_swap "$ARG" | ./checker_linux "$ARG")

	# Count the number of lines printed by checker
	line_count=$(./push_swap "$ARG" | wc -l)

	if [[ "$output" == "OK" ]]; then
		echo -e "${GREEN}OK: output complies with checker${NC}"
	else
		echo -e "${RED}Test failed: Argument '$ARG' did not produce correct output${NC}"
		echo "Actual output:"
		echo "$output"
	fi
	echo "Number of operations: $line_count"
	echo "-----------------------------"
done
