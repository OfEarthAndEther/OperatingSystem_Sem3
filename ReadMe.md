"# Operating System All Work"
---
> # Steps for initializing a directory or file editing or displaying local files on Github etc
> echo "# OperatingSystem_Sem3" >> README.md  
> git init  
> git add README.md  
> git commit -m "first commit"  
> git branch -M main  
> git remote add origin https://github.com/SRISHTInsut/OperatingSystem_Sem3.git  
> git push -u origin main  
---
### What I changed and why:

1.  **Headings (`#`, `##`, `###`)**: You were using the `#` symbol for everything. To create a hierarchy, you need to use more `#` symbols for sub-headings.
    * `#` is for the top-level title.
    * `##` is for main sections.
    * `###` is for sub-sections.
    This creates a clear, structured document outline. I've changed your sub-headings like "1. System Calls" and "FCFS" to use `##` and `###` respectively, which is standard Markdown practice.

2.  **Lists (`-` or `+`)**: The list items you had for `FCFS` were a bit off. When using a list, make sure the bullet point (`-`, `*`, or `+`) is followed by a space.
    * I've changed your `+` to `###` to represent a heading.
    * I've removed the `+` and `>`, since a list is sufficient.

3.  **Blockquotes (`>`)**: You were using `>` with a `+` for your notes. The `>` symbol is for blockquotes, which are used for quoted text.
    * I've kept the `>` for the notes under FCFS as this is a valid way to emphasize them, but using a normal bulleted list is more common. I've also removed the escaped parenthesis `\(` and `\)`, as they are not needed in this context. Markdown parsers are smart enough to understand that these are not link syntax.

4.  **Code Block**: Your C++ code block had some extra spaces and a stray `+`. The correct syntax is to place the three backticks on a new line directly before and after the code.
    * I've removed the extra spaces before the backticks and placed the entire code block so it is not indented at all, which is the correct way to format a fenced code block.

By making these changes, your document will be much more readable, professional, and compatible with all Markdown renderers.
---

"# OperatingSystem_Sem3"
# 1. System Calls
# 2. Shell Commands
# 3. CPU Scheduling Algo
  + # FCFS
    > First Come First Serve  
    > Ready Queue -> FIFO  
    > Not Optimal \(Changing order of the processes has a significant in avg_waitingTime.\)
  ```C++
    #include <iostream>
    using namespace std;

    int main(){
      return 0;
    };
  + # SJF
# 4. Process Synchronization
# 5. Deadlock
