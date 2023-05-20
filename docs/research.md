# DOCS RESEARCH

## Readline

### `rl_on_new_line()`

- ***Prototype***:
	```c
	void rl_on_new_line (void);
	```

- ***Description***:
	Tell the update routines that we have moved onto a new (empty) line, usually after ouputting a newline.

---

### `rl_redisplay()`

- ***Prototype***:
	```c
	void rl_redisplay (void);
	```

- ***Description***:
	Change what's displayed on the screen to reflect the current contents of `rl_line_buffer`.

---

### `rl_replace_line()`

- ***Prototype***:
	```c
	void rl_replace_line (const char *text, int clear_undo);
	```
- ***Description***:
	Replace the contents of `rl_line_buffer` with text. The point and mark are preserved, if possible. If clear_undo is non-zero, the undo list associated with the current line is cleared.

---

> - *Links*:
	- https://web.mit.edu/gnu/doc/html/rlman_2.html
	- https://tiswww.case.edu/php/chet/readline/readline.html
