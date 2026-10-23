import docx
from docx import Document
from docx.shared import Inches, Pt, RGBColor
from docx.enum.text import WD_ALIGN_PARAGRAPH
from docx.enum.table import WD_TABLE_ALIGNMENT
from docx.oxml import OxmlElement, parse_xml
from docx.oxml.ns import qn, nsdecls

def create_exam_guide():
    doc = Document()

    # Configure Margins (1 inch all around)
    for section in doc.sections:
        section.top_margin = Inches(1.0)
        section.bottom_margin = Inches(1.0)
        section.left_margin = Inches(1.0)
        section.right_margin = Inches(1.0)

    # XML Helper Functions
    def set_cell_background(cell, fill_hex):
        tcPr = cell._tc.get_or_add_tcPr()
        shd = parse_xml(f'<w:shd {nsdecls("w")} w:fill="{fill_hex}"/>')
        tcPr.append(shd)

    def set_cell_margins(cell, top=120, bottom=120, left=180, right=180):
        tcPr = cell._tc.get_or_add_tcPr()
        tcMar = parse_xml(
            f'<w:tcMar {nsdecls("w")}>'
            f'<w:top w:w="{top}" w:type="dxa"/>'
            f'<w:bottom w:w="{bottom}" w:type="dxa"/>'
            f'<w:left w:w="{left}" w:type="dxa"/>'
            f'<w:right w:w="{right}" w:type="dxa"/>'
            f'</w:tcMar>'
        )
        tcPr.append(tcMar)

    def set_callout_borders(cell, border_color="2B6CB0", border_size="24"):
        tcPr = cell._tc.get_or_add_tcPr()
        tcBorders = parse_xml(
            f'<w:tcBorders {nsdecls("w")}>'
            f'<w:top w:val="none"/>'
            f'<w:left w:val="single" w:sz="{border_size}" w:space="0" w:color="{border_color}"/>'
            f'<w:bottom w:val="none"/>'
            f'<w:right w:val="none"/>'
            f'</w:tcBorders>'
        )
        tcPr.append(tcBorders)

    def add_code_box(code_text):
        tbl = doc.add_table(rows=1, cols=1)
        tbl.alignment = WD_TABLE_ALIGNMENT.CENTER
        cell = tbl.cell(0, 0)
        set_cell_background(cell, "F7FAFC")
        set_cell_margins(cell, top=100, bottom=100, left=180, right=180)
        
        tcPr = cell._tc.get_or_add_tcPr()
        borders = parse_xml(
            f'<w:tcBorders {nsdecls("w")}>'
            f'<w:top w:val="single" w:sz="6" w:space="0" w:color="E2E8F0"/>'
            f'<w:left w:val="single" w:sz="18" w:space="0" w:color="3182CE"/>'
            f'<w:bottom w:val="single" w:sz="6" w:space="0" w:color="E2E8F0"/>'
            f'<w:right w:val="single" w:sz="6" w:space="0" w:color="E2E8F0"/>'
            f'</w:tcBorders>'
        )
        tcPr.append(borders)
        
        p = cell.paragraphs[0]
        p.paragraph_format.space_before = Pt(3)
        p.paragraph_format.space_after = Pt(3)
        p.paragraph_format.line_spacing = 1.15
        run = p.add_run(code_text.strip())
        run.font.name = "Consolas"
        run.font.size = Pt(9)
        run.font.color.rgb = RGBColor(0x2D, 0x37, 0x48)

    def add_tip_box(tip_text):
        tbl = doc.add_table(rows=1, cols=1)
        tbl.alignment = WD_TABLE_ALIGNMENT.CENTER
        cell = tbl.cell(0, 0)
        set_cell_background(cell, "EBF8FF")
        set_cell_margins(cell, top=100, bottom=100, left=180, right=180)
        set_callout_borders(cell, border_color="2B6CB0", border_size="24")
        
        p = cell.paragraphs[0]
        p.paragraph_format.space_before = Pt(3)
        p.paragraph_format.space_after = Pt(3)
        p.paragraph_format.line_spacing = 1.15
        
        label = p.add_run("Exam & Viva Tip: ")
        label.bold = True
        label.font.name = "Calibri"
        label.font.size = Pt(9.5)
        label.font.color.rgb = RGBColor(0x1B, 0x36, 0x5D)
        
        content = p.add_run(tip_text.strip())
        content.font.name = "Calibri"
        content.font.size = Pt(9.5)
        content.font.color.rgb = RGBColor(0x2D, 0x37, 0x48)

    # Document Header / Title
    title_p = doc.add_paragraph()
    title_p.paragraph_format.space_before = Pt(0)
    title_p.paragraph_format.space_after = Pt(4)
    title_p.paragraph_format.alignment = WD_ALIGN_PARAGRAPH.CENTER
    run_title = title_p.add_run("DATA STRUCTURES & ALGORITHMS")
    run_title.bold = True
    run_title.font.name = "Calibri"
    run_title.font.size = Pt(24)
    run_title.font.color.rgb = RGBColor(0x1B, 0x36, 0x5D)

    sub_p = doc.add_paragraph()
    sub_p.paragraph_format.space_before = Pt(0)
    sub_p.paragraph_format.space_after = Pt(14)
    sub_p.paragraph_format.alignment = WD_ALIGN_PARAGRAPH.CENTER
    run_sub = sub_p.add_run("Practical Examination Preparation & Algorithm Revision Guide (32 Programs)")
    run_sub.font.name = "Calibri"
    run_sub.font.size = Pt(13)
    run_sub.font.color.rgb = RGBColor(0x4A, 0x55, 0x68)

    # Overview Box
    ov_tbl = doc.add_table(rows=1, cols=1)
    ov_tbl.alignment = WD_TABLE_ALIGNMENT.CENTER
    ov_cell = ov_tbl.cell(0, 0)
    set_cell_background(ov_cell, "F7FAFC")
    set_cell_margins(ov_cell, top=140, bottom=140, left=200, right=200)
    tcPr = ov_cell._tc.get_or_add_tcPr()
    borders = parse_xml(
        f'<w:tcBorders {nsdecls("w")}>'
        f'<w:top w:val="single" w:sz="12" w:space="0" w:color="CBD5E0"/>'
        f'<w:left w:val="single" w:sz="12" w:space="0" w:color="CBD5E0"/>'
        f'<w:bottom w:val="single" w:sz="12" w:space="0" w:color="CBD5E0"/>'
        f'<w:right w:val="single" w:sz="12" w:space="0" w:color="CBD5E0"/>'
        f'</w:tcBorders>'
    )
    tcPr.append(borders)
    
    ov_p = ov_cell.paragraphs[0]
    ov_p.paragraph_format.space_before = Pt(2)
    ov_p.paragraph_format.space_after = Pt(2)
    ov_p.paragraph_format.line_spacing = 1.2
    ov_run = ov_p.add_run(
        "Purpose of this Guide: This revision handbook is tailored specifically for written lab exams, practical evaluations, and external viva voce. "
        "Every algorithm is articulated in crystal-clear, step-by-step simple English that can be written word-for-word in answer sheets. "
        "Each topic includes the core concept, simplified algorithm, heart-of-the-code snippet, time/space complexity, and high-yield viva questions."
    )
    ov_run.font.name = "Calibri"
    ov_run.font.size = Pt(10)
    ov_run.font.color.rgb = RGBColor(0x2D, 0x37, 0x48)

    doc.add_paragraph().paragraph_format.space_after = Pt(12)

    # Index Summary Table
    idx_p = doc.add_paragraph()
    idx_p.paragraph_format.space_before = Pt(10)
    idx_p.paragraph_format.space_after = Pt(6)
    idx_run = idx_p.add_run("Quick Reference Index")
    idx_run.bold = True
    idx_run.font.name = "Calibri"
    idx_run.font.size = Pt(14)
    idx_run.font.color.rgb = RGBColor(0x1B, 0x36, 0x5D)

    summary_data = [
        ("Section 1: Recursion & Math", "5 Programs", "Ackermann, Factorial, Fibonacci, GCD, Tower of Hanoi"),
        ("Section 2: Stack Applications", "8 Programs", "Stack Array, Stack Linked List, ADT, Decimal to Binary, Reverse String, Infix->Postfix, Infix->Prefix, Postfix Eval"),
        ("Section 3: Queue Applications", "6 Programs", "Queue Array, Queue Linked List, ADT, Circular Queue, Deque, Priority Queue"),
        ("Section 4: Linked Lists", "8 Programs", "Singly LL, LL ADT, Doubly LL, Concatenate, Ordered List, Reverse LL, Poly Eval, Poly Add/Sub"),
        ("Section 5: Trees & Traversals", "5 Programs", "Binary Tree Array, BST (Min/Max/Search), Non-Rec Preorder, Non-Rec Inorder, Non-Rec Postorder")
    ]

    sum_table = doc.add_table(rows=len(summary_data) + 1, cols=3)
    sum_table.alignment = WD_TABLE_ALIGNMENT.CENTER
    headers = ["Section Name", "Count", "Topics Covered"]
    col_widths = [Inches(2.0), Inches(1.0), Inches(3.5)]

    for c_idx, h_text in enumerate(headers):
        c = sum_table.cell(0, c_idx)
        c.width = col_widths[c_idx]
        set_cell_background(c, "1B365D")
        set_cell_margins(c, top=100, bottom=100, left=140, right=140)
        p = c.paragraphs[0]
        p.paragraph_format.space_before = Pt(2)
        p.paragraph_format.space_after = Pt(2)
        r = p.add_run(h_text)
        r.bold = True
        r.font.name = "Calibri"
        r.font.size = Pt(10)
        r.font.color.rgb = RGBColor(0xFF, 0xFF, 0xFF)

    for r_idx, row_data in enumerate(summary_data):
        row_cell = sum_table.rows[r_idx + 1]
        bg = "F7FAFC" if r_idx % 2 == 1 else "FFFFFF"
        for c_idx, val in enumerate(row_data):
            c = row_cell.cells[c_idx]
            c.width = col_widths[c_idx]
            set_cell_background(c, bg)
            set_cell_margins(c, top=80, bottom=80, left=140, right=140)
            p = c.paragraphs[0]
            p.paragraph_format.space_before = Pt(2)
            p.paragraph_format.space_after = Pt(2)
            r = p.add_run(val)
            r.font.name = "Calibri"
            r.font.size = Pt(9.5)
            r.font.color.rgb = RGBColor(0x2D, 0x37, 0x48)

    doc.add_page_break()

    # Section Renderer
    def add_section_header(section_title):
        p = doc.add_paragraph()
        p.paragraph_format.space_before = Pt(16)
        p.paragraph_format.space_after = Pt(8)
        run = p.add_run(section_title)
        run.bold = True
        run.font.name = "Calibri"
        run.font.size = Pt(18)
        run.font.color.rgb = RGBColor(0x1B, 0x36, 0x5D)

    def add_topic(num, title, file_name, aim, concept, steps, code_snippet, complexity, exam_tip):
        # Topic Title
        tp = doc.add_paragraph()
        tp.paragraph_format.space_before = Pt(12)
        tp.paragraph_format.space_after = Pt(2)
        r_num = tp.add_run(f"{num}. {title} ")
        r_num.bold = True
        r_num.font.name = "Calibri"
        r_num.font.size = Pt(13)
        r_num.font.color.rgb = RGBColor(0x2B, 0x6C, 0xB0)

        r_file = tp.add_run(f"[{file_name}]")
        r_file.font.name = "Consolas"
        r_file.font.size = Pt(10)
        r_file.font.color.rgb = RGBColor(0x71, 0x80, 0x96)

        # Aim
        p_aim = doc.add_paragraph()
        p_aim.paragraph_format.space_before = Pt(1)
        p_aim.paragraph_format.space_after = Pt(2)
        r_aim_lbl = p_aim.add_run("Aim: ")
        r_aim_lbl.bold = True
        r_aim_lbl.font.size = Pt(10)
        r_aim_lbl.font.color.rgb = RGBColor(0x1B, 0x36, 0x5D)
        r_aim_val = p_aim.add_run(aim)
        r_aim_val.font.size = Pt(10)

        # Concept
        p_con = doc.add_paragraph()
        p_con.paragraph_format.space_before = Pt(1)
        p_con.paragraph_format.space_after = Pt(4)
        r_con_lbl = p_con.add_run("Core Concept: ")
        r_con_lbl.bold = True
        r_con_lbl.font.size = Pt(10)
        r_con_lbl.font.color.rgb = RGBColor(0x1B, 0x36, 0x5D)
        r_con_val = p_con.add_run(concept)
        r_con_val.font.size = Pt(10)

        # Algorithm Header
        p_alg = doc.add_paragraph()
        p_alg.paragraph_format.space_before = Pt(3)
        p_alg.paragraph_format.space_after = Pt(2)
        r_alg_lbl = p_alg.add_run("Algorithm (Simple Steps for Exam):")
        r_alg_lbl.bold = True
        r_alg_lbl.font.size = Pt(10.5)
        r_alg_lbl.font.color.rgb = RGBColor(0x1B, 0x36, 0x5D)

        # Algorithm Steps
        for step in steps:
            p_step = doc.add_paragraph()
            p_step.paragraph_format.left_indent = Inches(0.25)
            p_step.paragraph_format.space_before = Pt(1)
            p_step.paragraph_format.space_after = Pt(2)
            p_step.paragraph_format.line_spacing = 1.15
            r_st = p_step.add_run(step)
            r_st.font.name = "Calibri"
            r_st.font.size = Pt(9.5)
            r_st.font.color.rgb = RGBColor(0x2D, 0x37, 0x48)

        # Code Box
        p_c_lbl = doc.add_paragraph()
        p_c_lbl.paragraph_format.space_before = Pt(3)
        p_c_lbl.paragraph_format.space_after = Pt(2)
        r_c_lbl = p_c_lbl.add_run("Key Logic Snippet:")
        r_c_lbl.bold = True
        r_c_lbl.font.size = Pt(10)
        r_c_lbl.font.color.rgb = RGBColor(0x1B, 0x36, 0x5D)

        add_code_box(code_snippet)

        # Complexity
        p_cpx = doc.add_paragraph()
        p_cpx.paragraph_format.space_before = Pt(3)
        p_cpx.paragraph_format.space_after = Pt(2)
        r_cpx_lbl = p_cpx.add_run("Complexity: ")
        r_cpx_lbl.bold = True
        r_cpx_lbl.font.size = Pt(9.5)
        r_cpx_lbl.font.color.rgb = RGBColor(0x1B, 0x36, 0x5D)
        r_cpx_val = p_cpx.add_run(complexity)
        r_cpx_val.font.size = Pt(9.5)

        # Viva Tip
        add_tip_box(exam_tip)

        doc.add_paragraph().paragraph_format.space_after = Pt(6)

    # ==========================================
    # SECTION 1: RECURSION & MATHEMATICAL ALGORITHMS
    # ==========================================
    add_section_header("Section 1: Recursion & Mathematical Algorithms")

    add_topic(
        num=1,
        title="Ackermann Function",
        file_name="Ackerman.c",
        aim="To compute the value of the Ackermann function A(m, n) for two non-negative integers using recursion.",
        concept="Ackermann is a classic example of a total computable function that is not primitive recursive. It features deep nested recursion across two variables.",
        steps=[
            "Step 1: Start.",
            "Step 2: Read two non-negative integers m and n from the user.",
            "Step 3: Define ackermann(m, n):",
            "         a. If m == 0, return n + 1 (Base Case 1).",
            "         b. If n == 0, return ackermann(m - 1, 1) (Base Case 2).",
            "         c. Else, return ackermann(m - 1, ackermann(m, n - 1)) (Recursive Step).",
            "Step 4: Print the computed Ackermann value.",
            "Step 5: Stop."
        ],
        code_snippet="""int ackermann(int m, int n) {
    if (m == 0) return n + 1;
    if (n == 0) return ackermann(m - 1, 1);
    return ackermann(m - 1, ackermann(m, n - 1));
}""",
        complexity="Time: Extremely fast exponential growth (hyper-exponential). Space: O(m) stack depth.",
        exam_tip="Examiners often ask for small test values: A(1, 2) = 4, A(2, 2) = 7, A(2, 3) = 9. Avoid testing m >= 4 because it causes stack overflow quickly!"
    )

    add_topic(
        num=2,
        title="Factorial of a Number",
        file_name="Factorial.c",
        aim="To compute the factorial of a given integer n recursively.",
        concept="Factorial is defined recursively as n! = n * (n - 1)!, with the base condition that 0! = 1 and 1! = 1.",
        steps=[
            "Step 1: Start.",
            "Step 2: Read integer n.",
            "Step 3: Define factorial(n):",
            "         a. If n <= 1, return 1 (Base Case).",
            "         b. Else, return n * factorial(n - 1) (Recursive Step).",
            "Step 4: Print the factorial result.",
            "Step 5: Stop."
        ],
        code_snippet="""int factorial(int n) {
    if (n <= 1) return 1;
    return n * factorial(n - 1);
}""",
        complexity="Time: O(n). Space: O(n) auxiliary recursion stack space.",
        exam_tip="Notice the condition 'n <= 1'. It elegantly handles both n = 0 and n = 1 in a single check."
    )

    add_topic(
        num=3,
        title="Fibonacci Series",
        file_name="Fibonacci.c",
        aim="To generate and print the first n terms of the Fibonacci sequence using recursion.",
        concept="Each Fibonacci number is the sum of the two preceding ones: F(n) = F(n-1) + F(n-2), where F(0) = 0 and F(1) = 1.",
        steps=[
            "Step 1: Start.",
            "Step 2: Read total number of terms n.",
            "Step 3: Define fibonacci(n):",
            "         a. If n <= 1, return n (Base Case: returns 0 for 0, 1 for 1).",
            "         b. Else, return fibonacci(n - 1) + fibonacci(n - 2).",
            "Step 4: Loop variable i from 0 to n - 1, calling and printing fibonacci(i).",
            "Step 5: Stop."
        ],
        code_snippet="""int fibonacci(int n) {
    if (n <= 1) return n;
    return fibonacci(n - 1) + fibonacci(n - 2);
}""",
        complexity="Time: O(2^n) exponential per call due to recursive branching. Space: O(n) stack frames.",
        exam_tip="Viva Question: Why is recursive Fibonacci considered inefficient? Answer: Because it recalculates the same subproblems multiple times (e.g., fib(3) is calculated multiple times)."
    )

    add_topic(
        num=4,
        title="Greatest Common Denominator (GCD)",
        file_name="Greatest_Common_Denominator.c",
        aim="To find the Greatest Common Divisor of two numbers using Euclid's Algorithm.",
        concept="Euclid's rule states that GCD(a, b) = GCD(b, a % b). When the divisor b reaches 0, the current value of a is the GCD.",
        steps=[
            "Step 1: Start.",
            "Step 2: Read two integers a and b.",
            "Step 3: Define gcd(a, b):",
            "         a. If b == 0, return a (Base Case).",
            "         b. Else, return gcd(b, a % b) (Recursive Step).",
            "Step 4: Print the computed GCD value.",
            "Step 5: Stop."
        ],
        code_snippet="""int gcd(int a, int b) {
    if (b == 0) return a;
    return gcd(b, a % b);
}""",
        complexity="Time: O(log(min(a, b))). Space: O(log(min(a, b))) stack frames.",
        exam_tip="What happens if a < b initially? Answer: In the very first call, a % b equals a, so gcd(b, a % b) automatically swaps the two numbers without needing a temporary variable!"
    )

    add_topic(
        num=5,
        title="Tower of Hanoi",
        file_name="Tower_Of_Honai.c",
        aim="To solve the Tower of Hanoi puzzle for n disks from source peg A to destination peg C using auxiliary peg B.",
        concept="To move n disks: move n-1 disks to aux peg, move the largest disk to dest peg, then move the n-1 disks from aux to dest peg.",
        steps=[
            "Step 1: Start.",
            "Step 2: Read number of disks n.",
            "Step 3: Define hanoi(n, from, to, aux):",
            "         a. If n > 0:",
            "             i. Call hanoi(n - 1, from, aux, to) -> moves n-1 disks to auxiliary peg.",
            "            ii. Print: 'Move disk n from peg {from} to peg {to}'.",
            "           iii. Call hanoi(n - 1, aux, to, from) -> moves n-1 disks to destination peg.",
            "Step 4: In main(), call hanoi(n, 'A', 'C', 'B').",
            "Step 5: Stop."
        ],
        code_snippet="""void hanoi(int n, char from, char to, char aux) {
    if (n > 0) {
        hanoi(n - 1, from, aux, to);
        printf("Move disk %d from %c to %c\\n", n, from, to);
        hanoi(n - 1, aux, to, from);
    }
}""",
        complexity="Time: O(2^n - 1) moves (Exponential). Space: O(n) stack depth.",
        exam_tip="Common viva question: What is the minimum number of moves required for n disks? Answer: Exactly 2^n - 1 moves. For n = 3, exactly 7 moves."
    )

    # ==========================================
    # SECTION 2: STACK APPLICATIONS & IMPLEMENTATIONS
    # ==========================================
    add_section_header("Section 2: Stack Applications & Implementations")

    add_topic(
        num=6,
        title="Stack Implementation Using Array",
        file_name="Stack_Using_Array.c",
        aim="To implement a Last-In-First-Out (LIFO) Stack using an array with Push, Pop, and Display operations.",
        concept="A stack uses a single integer index 'top', initialized to -1. Push increments top; Pop decrements top.",
        steps=[
            "Step 1: Start and declare stack[MAX] and top = -1.",
            "Step 2: push():",
            "         a. If top == MAX - 1, print 'Stack Overflow' and exit.",
            "         b. Else, increment top and read value into stack[++top].",
            "Step 3: pop():",
            "         a. If top == -1, print 'Stack Underflow' and exit.",
            "         b. Else, print popped value stack[top--].",
            "Step 4: display():",
            "         a. If top == -1, print 'Stack is empty'.",
            "         b. Else, loop i from top down to 0 and print stack[i].",
            "Step 5: In main(), provide a menu-driven loop (1: Push, 2: Pop, 3: Display, 4: Exit)."
        ],
        code_snippet="""void push() {
    if (top == MAX - 1) { printf("Stack Overflow\\n"); return; }
    printf("Enter value: ");
    scanf("%d", &stack[++top]);
}
void pop() {
    if (top == -1) { printf("Stack Underflow\\n"); return; }
    printf("Popped value: %d\\n", stack[top--]);
}""",
        complexity="Push: O(1), Pop: O(1), Display: O(n). Auxiliary Space: O(MAX).",
        exam_tip="Always check overflow BEFORE incrementing top, and check underflow BEFORE decrementing top."
    )

    add_topic(
        num=7,
        title="Stack Implementation Using Linked List",
        file_name="Stack_Using_Linked_List.c",
        aim="To implement a dynamic stack using a Singly Linked List.",
        concept="The pointer 'top' always points to the first (head) node of the linked list. Pushing inserts at head; popping deletes from head.",
        steps=[
            "Step 1: Start and define struct Node { int data; struct Node *next; } and top = NULL.",
            "Step 2: push():",
            "         a. Allocate newNode = malloc(sizeof(struct Node)).",
            "         b. Read value into newNode->data.",
            "         c. Link newNode->next = top.",
            "         d. Update top = newNode.",
            "Step 3: pop():",
            "         a. If top == NULL, print 'Stack is empty' and exit.",
            "         b. Set temp = top. Print temp->data.",
            "         c. Advance top = top->next.",
            "         d. Free temp.",
            "Step 4: display():",
            "         a. If top == NULL, print 'Stack is empty'.",
            "         b. Else, traverse temp from top to NULL and print each temp->data."
        ],
        code_snippet="""void push() {
    struct Node *newNode = malloc(sizeof(struct Node));
    scanf("%d", &newNode->data);
    newNode->next = top;
    top = newNode;
}
void pop() {
    if (top == NULL) return;
    struct Node *temp = top;
    top = top->next;
    free(temp);
}""",
        complexity="Push: O(1), Pop: O(1), Display: O(n). Dynamic Space: O(n).",
        exam_tip="Why prefer a linked stack over an array stack? Answer: Linked stack never suffers from a fixed-size overflow; it grows dynamically in heap memory."
    )

    add_topic(
        num=8,
        title="Stack ADT (Generic Multi-Type)",
        file_name="Stack_ADT.c",
        aim="To implement a full Abstract Data Type (ADT) Stack supporting multiple data types (int, float, char, string).",
        concept="Abstract Data Types separate the logical model from data representation. Using void* data and a char type flag allows heterogeneous data storage.",
        steps=[
            "Step 1: Define struct Node { void *data; char type; struct Node *next; }.",
            "Step 2: Implement makeNode(char *s): detect if string is char ('c'), float ('f'), int ('i'), or string ('s'); allocate void* memory and store value.",
            "Step 3: Implement push() -> inserts at top; pop() -> deletes from top and frees void* data.",
            "Step 4: Implement peek() -> prints top element without removing it.",
            "Step 5: Implement search() -> uses match() helper to find position from top.",
            "Step 6: Implement count() and destroyStack() to free all heap nodes on exit."
        ],
        code_snippet="""int match(struct Node *a, struct Node *b) {
    if (a->type != b->type) return 0;
    if (a->type == 'i') return *(int *)a->data == *(int *)b->data;
    if (a->type == 'f') return *(float *)a->data == *(float *)b->data;
    if (a->type == 'c') return *(char *)a->data == *(char *)b->data;
    return strcmp((char *)a->data, (char *)b->data) == 0;
}""",
        complexity="Push/Pop/Peek: O(1). Search/Display/Destroy: O(n).",
        exam_tip="In ADT questions, always mention data encapsulation: internal node representations are manipulated only via ADT interface functions."
    )

    add_topic(
        num=9,
        title="Decimal to Binary Conversion Using Stack",
        file_name="Stack_Decimal_To_Binary.c",
        aim="To convert a positive decimal number into its binary equivalent using a stack.",
        concept="Successive division by 2 produces binary digits in reverse order (least significant bit first). A LIFO stack naturally reverses them to most significant bit first.",
        steps=[
            "Step 1: Start and initialize stack with top = -1.",
            "Step 2: Read decimal number.",
            "Step 3: Execute loop: do { push(decimal % 2); decimal /= 2; } while (decimal > 0);",
            "Step 4: While stack is not empty (top != -1):",
            "         a. Pop element and print it.",
            "Step 5: Stop."
        ],
        code_snippet="""do {
    push(decimal % 2);
    decimal /= 2;
} while (decimal > 0);

while (top != -1) {
    printf("%d", pop());
}""",
        complexity="Time: O(log2(n)). Space: O(log2(n)).",
        exam_tip="Using do-while guarantees that if the input is decimal = 0, the program correctly pushes 0 and outputs '0' without needing an extra if-condition."
    )

    add_topic(
        num=10,
        title="Reverse String Using Stack",
        file_name="Reverse_String_Using_Stack.c",
        aim="To reverse any given input string using character stack operations.",
        concept="Because a stack operates on Last-In-First-Out, pushing letters from left-to-right and then popping them produces the exact reversed string.",
        steps=[
            "Step 1: Start and initialize char stack[MAX] with top = -1.",
            "Step 2: Read input string using scanf(\" %[^\\n]\", str).",
            "Step 3: Loop i from 0 until str[i] == '\\0', calling push(str[i]).",
            "Step 4: Loop while top != -1, printing each pop() character.",
            "Step 5: Stop."
        ],
        code_snippet="""for (i = 0; str[i] != '\\0'; i++) {
    push(str[i]);
}
while (top != -1) {
    printf("%c", pop());
}""",
        complexity="Time: O(n). Space: O(n).",
        exam_tip="Never use gets() in modern C exams as it is dangerous and deprecated. Always use scanf(\" %[^\\n]\", str) or fgets()."
    )

    add_topic(
        num=11,
        title="Infix to Postfix Conversion",
        file_name="Infix_To_Postfix.c",
        aim="To convert an infix expression (e.g., A+B*(C^D-E)) to postfix using an operator stack.",
        concept="Operands are directly outputted. Operators are pushed to stack based on precedence: ^ (3) > *, / (2) > +, - (1). Parentheses handle sub-expressions.",
        steps=[
            "Step 1: Initialize operator stack with top = -1 and index j = 0 for postfix.",
            "Step 2: Scan infix string from left to right:",
            "         a. If character is alphanumeric (operand): postfix[j++] = ch.",
            "         b. If character is '(': push(ch).",
            "         c. If character is ')': pop from stack to postfix until '(' is encountered; discard '('.",
            "         d. If operator: while top != -1 and priority(stack[top]) >= priority(ch), pop to postfix; then push(ch).",
            "Step 3: Pop all remaining operators from stack into postfix.",
            "Step 4: Terminate postfix string with '\\0' and print result."
        ],
        code_snippet="""int priority(char ch) {
    if (ch == '^') return 3;
    if (ch == '*' || ch == '/') return 2;
    if (ch == '+' || ch == '-') return 1;
    return 0;
}
// Inside scan loop:
while (top != -1 && priority(stack[top]) >= priority(ch)) {
    postfix[j++] = pop();
}
push(ch);""",
        complexity="Time: O(n). Space: O(n).",
        exam_tip="Crucial rule for viva: Parentheses never appear in the final postfix expression!"
    )

    add_topic(
        num=12,
        title="Infix to Prefix Conversion",
        file_name="Infix_To_Prefix.c",
        aim="To convert an infix expression to prefix notation using an operator stack.",
        concept="Prefix scans the infix expression in REVERSE (right-to-left). Operators use strictly greater priority (>) instead of (>=). The output string is reversed at the end.",
        steps=[
            "Step 1: Scan infix expression from right to left (i = len - 1 down to 0):",
            "         a. If operand: prefix[j++] = ch.",
            "         b. If ')': push(')').",
            "         c. If '(': pop from stack to prefix until ')' is popped; discard ')'.",
            "         d. If operator: while top != -1 and priority(stack[top]) > priority(ch), pop to prefix; then push(ch).",
            "Step 2: Pop all remaining operators from stack to prefix.",
            "Step 3: Terminate string with '\\0'.",
            "Step 4: Reverse prefix string in-place (swap prefix[i] and prefix[j]).",
            "Step 5: Print final prefix expression."
        ],
        code_snippet="""for (i = strlen(infix) - 1; i >= 0; i--) {
    // Note: strictly greater priority (>) when scanning right to left!
    while (top != -1 && priority(stack[top]) > priority(ch)) {
        prefix[j++] = pop();
    }
    push(ch);
}
// Reverse result string at the end
for (i = 0, j--; i < j; i++, j--) {
    char t = prefix[i]; prefix[i] = prefix[j]; prefix[j] = t;
}""",
        complexity="Time: O(n). Space: O(n).",
        exam_tip="Why is strictly greater (>) priority used? Because when scanning right-to-left, operators with equal precedence must maintain left-to-right evaluation order in the final result."
    )

    add_topic(
        num=13,
        title="Postfix Expression Evaluation",
        file_name="Evaluate_Postfix.c",
        aim="To evaluate a postfix arithmetic expression using an integer operand stack.",
        concept="When digits are scanned, push their numeric values. When an operator is scanned, pop the two most recent operands, apply the operator, and push the result back.",
        steps=[
            "Step 1: Initialize integer stack with top = -1.",
            "Step 2: Scan postfix expression character by character:",
            "         a. If character is digit (isdigit): push(ch - '0').",
            "         b. If character is operator: pop b = pop(), then pop a = pop().",
            "            Apply operation: switch(ch) -> case '+': push(a + b); case '-': push(a - b); ...",
            "Step 3: When scan finishes, final answer is pop().",
            "Step 4: Print the result."
        ],
        code_snippet="""if (isdigit(exp[i])) {
    push(exp[i] - '0');
} else {
    b = pop(); // Second operand
    a = pop(); // First operand
    switch (exp[i]) {
        case '+': push(a + b); break;
        case '-': push(a - b); break;
        case '*': push(a * b); break;
        case '/': push(a / b); break;
    }
}""",
        complexity="Time: O(n). Space: O(n).",
        exam_tip="Common pitfall in exams: Order of operands! The FIRST popped element is b (right operand), and the SECOND popped element is a (left operand). You must compute a - b, NOT b - a."
    )

    # ==========================================
    # SECTION 3: QUEUE APPLICATIONS & IMPLEMENTATIONS
    # ==========================================
    add_section_header("Section 3: Queue Applications & Implementations")

    add_topic(
        num=14,
        title="Linear Queue Using Array",
        file_name="Queue_Using_Array.c",
        aim="To implement a First-In-First-Out (FIFO) Linear Queue using an array.",
        concept="Linear queue uses two indices: front (points to first element) and rear (points to last element). Both start at -1.",
        steps=[
            "Step 1: Declare queue[MAX], front = -1, rear = -1.",
            "Step 2: enqueue():",
            "         a. If rear == MAX - 1, print 'Queue is full' and return.",
            "         b. If front == -1, set front = 0.",
            "         c. Read value into queue[++rear].",
            "Step 3: dequeue():",
            "         a. If front == -1 or front > rear, print 'Queue is empty' and return.",
            "         b. Print deleted value queue[front++].",
            "         c. If front > rear, reset front = rear = -1.",
            "Step 4: display():",
            "         a. Loop i from front to rear and print queue[i]."
        ],
        code_snippet="""void enqueue() {
    if (rear == MAX - 1) { printf("Queue is full.\\n"); return; }
    if (front == -1) front = 0;
    scanf("%d", &queue[++rear]);
}
void dequeue() {
    if (front == -1 || front > rear) { printf("Queue is empty.\\n"); return; }
    printf("Deleted value: %d\\n", queue[front++]);
    if (front > rear) front = rear = -1;
}""",
        complexity="Enqueue: O(1), Dequeue: O(1), Display: O(n). Space: O(MAX).",
        exam_tip="Viva Question: What is the main drawback of a Linear Queue? Answer: 'False Overflow'—even if space is free at the front of the array after dequeuing, new elements cannot be enqueued because rear has reached MAX-1."
    )

    add_topic(
        num=15,
        title="Queue Using Linked List",
        file_name="Queue_Using_Linked_List.c",
        aim="To implement a dynamic FIFO Queue using a singly linked list.",
        concept="Two pointers are maintained: front (points to head for fast deletion) and rear (points to tail for fast insertion).",
        steps=[
            "Step 1: Define struct Node { int data; struct Node *next; } and front = NULL, rear = NULL.",
            "Step 2: enqueue():",
            "         a. Allocate newNode = malloc(sizeof(struct Node)). Read data, set next = NULL.",
            "         b. If front == NULL, set front = rear = newNode.",
            "         c. Else set rear->next = newNode; rear = newNode;.",
            "Step 3: dequeue():",
            "         a. If front == NULL, print 'Queue is empty' and return.",
            "         b. Set temp = front, print temp->data.",
            "         c. Advance front = front->next. If front == NULL, set rear = NULL.",
            "         d. Free temp.",
            "Step 4: display(): traverse temp from front to NULL and print."
        ],
        code_snippet="""void enqueue() {
    struct Node *newNode = malloc(sizeof(struct Node));
    scanf("%d", &newNode->data);
    newNode->next = NULL;
    if (front == NULL) front = rear = newNode;
    else { rear->next = newNode; rear = newNode; }
}
void dequeue() {
    if (front == NULL) return;
    struct Node *temp = front;
    front = front->next;
    if (front == NULL) rear = NULL;
    free(temp);
}""",
        complexity="Enqueue: O(1), Dequeue: O(1). Space: O(n) dynamically.",
        exam_tip="Remember to set rear = NULL when front becomes NULL after deleting the last remaining node."
    )

    add_topic(
        num=16,
        title="Queue ADT (Generic Multi-Type)",
        file_name="Queue_ADT.c",
        aim="To implement a complete Queue ADT capable of enqueuing and dequeuing int, float, char, and string.",
        concept="Encapsulates FIFO queue operations with generic void* nodes and type tagging, featuring Enqueue, Dequeue, Front, Rear, Search, Count, and Destroy.",
        steps=[
            "Step 1: Define struct Node { void *data; char type; struct Node *next; } with front = NULL, rear = NULL.",
            "Step 2: enqueue(): parse input string with makeNode(), append at rear.",
            "Step 3: dequeue(): remove from front, print with printData(), free with freeNode().",
            "Step 4: frontElement() and rearElement(): peek at front/rear without removing.",
            "Step 5: search(): linear search matching value and type using match().",
            "Step 6: destroyQueue(): traverse and free all nodes."
        ],
        code_snippet="""void enqueue() {
    struct Node *n = makeNode(readValue());
    if (rear == NULL) front = rear = n;
    else { rear->next = n; rear = n; }
}""",
        complexity="Enqueue/Dequeue/Front/Rear: O(1). Display/Search/Destroy: O(n).",
        exam_tip="ADT principle: The main function interacts purely via function calls (enqueue, dequeue) without accessing pointers or internals directly."
    )

    add_topic(
        num=17,
        title="Circular Queue",
        file_name="Circular_Queue.c",
        aim="To implement a Circular Queue using an array to overcome the false overflow problem.",
        concept="The array wraps around circularly using modulo arithmetic: index = (index + 1) % MAX. When rear reaches MAX-1, it circles back to index 0 if space exists.",
        steps=[
            "Step 1: Declare queue[MAX], front = -1, rear = -1.",
            "Step 2: Full Condition: (rear + 1) % MAX == front.",
            "Step 3: Empty Condition: front == -1.",
            "Step 4: enqueue():",
            "         a. If full, print 'Queue is full' and return.",
            "         b. If front == -1, set front = rear = 0.",
            "         c. Else set rear = (rear + 1) % MAX.",
            "         d. Read value into queue[rear].",
            "Step 5: dequeue():",
            "         a. If empty, print 'Queue is empty' and return.",
            "         b. Print queue[front].",
            "         c. If front == rear (single element), reset front = rear = -1.",
            "         d. Else set front = (front + 1) % MAX.",
            "Step 6: display(): loop i = front; print queue[i]; if i == rear break; i = (i + 1) % MAX."
        ],
        code_snippet="""void enqueue() {
    if ((rear + 1) % MAX == front) { printf("Queue is full.\\n"); return; }
    if (front == -1) front = rear = 0;
    else rear = (rear + 1) % MAX;
    scanf("%d", &queue[rear]);
}
void dequeue() {
    if (front == -1) { printf("Queue is empty.\\n"); return; }
    printf("Deleted value: %d\\n", queue[front]);
    if (front == rear) front = rear = -1;
    else front = (front + 1) % MAX;
}""",
        complexity="Enqueue: O(1), Dequeue: O(1). Space: O(MAX).",
        exam_tip="Crucial formula to memorize: Full condition is (rear + 1) % MAX == front."
    )

    add_topic(
        num=18,
        title="Double Ended Queue (Deque)",
        file_name="Double_Ended_Queue.c",
        aim="To implement a Double Ended Queue allowing insertions and deletions at both ends.",
        concept="A Deque permits 4 operations: insertFront, insertRear, deleteFront, and deleteRear.",
        steps=[
            "Step 1: Declare deque[MAX], front = -1, rear = -1.",
            "Step 2: insertFront(): If front == 0, full at front. If empty (front == -1), front = rear = 0. Else front--. Scan deque[front].",
            "Step 3: insertRear(): If rear == MAX - 1, full at rear. If empty, front = rear = 0. Else rear++. Scan deque[rear].",
            "Step 4: deleteFront(): If empty, error. Print deque[front++]. If front > rear, reset front = rear = -1.",
            "Step 5: deleteRear(): If empty, error. Print deque[rear--]. If front > rear, reset front = rear = -1.",
            "Step 6: display(): loop i from front to rear and print deque[i]."
        ],
        code_snippet="""void insertFront() {
    if (front == 0) return;
    if (front == -1) front = rear = 0;
    else front--;
    scanf("%d", &deque[front]);
}
void deleteRear() {
    if (rear == -1 || front > rear) return;
    printf("Deleted: %d\\n", deque[rear--]);
    if (front > rear) front = rear = -1;
}""",
        complexity="All insertions and deletions: O(1). Display: O(n).",
        exam_tip="Viva Question: What are Input-Restricted and Output-Restricted Deques? Answer: Input-restricted allows insertion at only one end but deletion at both ends. Output-restricted allows deletion at only one end but insertion at both ends."
    )

    add_topic(
        num=19,
        title="Priority Queue (Ascending & Descending)",
        file_name="Priority_Queue_ASC_DEC.c",
        aim="To implement a Priority Queue where elements are organized by Ascending and Descending priority.",
        concept="In an Ascending Priority Queue, the smallest value has the highest priority. In a Descending Priority Queue, the largest value has the highest priority.",
        steps=[
            "Step 1: Declare queue[MAX] and n = 0.",
            "Step 2: insert(): read value into queue[n++].",
            "Step 3: ascending():",
            "         a. Sort queue using bubble sort in ascending order (queue[i] > queue[j] -> swap).",
            "         b. Print array as Ascending Priority.",
            "Step 4: descending():",
            "         a. Sort queue in descending order (queue[i] < queue[j] -> swap).",
            "         b. Print array as Descending Priority."
        ],
        code_snippet="""void ascending() {
    for (i = 0; i < n - 1; i++)
        for (j = i + 1; j < n; j++)
            if (queue[i] > queue[j]) {
                int t = queue[i]; queue[i] = queue[j]; queue[j] = t;
            }
    for (i = 0; i < n; i++) printf("%d ", queue[i]);
}""",
        complexity="Insert: O(1). Priority Sorting & Display: O(n^2).",
        exam_tip="In theoretical DSA, priority queues are often implemented using binary heaps for O(log n) efficiency, but for practical C exams, array sorting is the standard expected code."
    )

    # ==========================================
    # SECTION 4: LINKED LISTS & APPLICATIONS
    # ==========================================
    add_section_header("Section 4: Linked Lists & Applications")

    add_topic(
        num=20,
        title="Singly Linked List",
        file_name="Singly_Linked_List.c",
        aim="To implement a Singly Linked List with Insert (at end), Delete (by value), Search, and Display operations.",
        concept="A collection of dynamically allocated nodes, where each node contains data and a pointer (next) to the subsequent node.",
        steps=[
            "Step 1: Define struct Node { int data; struct Node *next; } and head = NULL.",
            "Step 2: insert(): allocate newNode, read data, set next = NULL. If head == NULL, head = newNode; else traverse to last node and link temp->next = newNode.",
            "Step 3: delete(): read value to delete. Traverse with temp and prev. If found, unlink node (if prev == NULL, head = temp->next; else prev->next = temp->next). Free temp.",
            "Step 4: search(): loop temp = head to NULL. If temp->data == value, print 'Found' and return.",
            "Step 5: display(): loop temp = head to NULL, print temp->data -> NULL."
        ],
        code_snippet="""void insert() {
    struct Node *newNode = malloc(sizeof(struct Node));
    scanf("%d", &newNode->data);
    newNode->next = NULL;
    if (head == NULL) { head = newNode; return; }
    struct Node *temp = head;
    while (temp->next != NULL) temp = temp->next;
    temp->next = newNode;
}""",
        complexity="Insert (at end): O(n). Delete: O(n). Search: O(n). Display: O(n).",
        exam_tip="Always check if head == NULL in delete() and search() before prompting the user for values."
    )

    add_topic(
        num=21,
        title="Singly Linked List ADT",
        file_name="Singly_Linked_List_ADT.c",
        aim="To implement a comprehensive Singly Linked List ADT with insertions, deletions, search, count, and destroy.",
        concept="Covers insertion and deletion at three specific positions: Beginning, End, and Any Arbitrary Position (index 1 to N).",
        steps=[
            "Step 1: insertBeginning(): new node points to head; head becomes new node.",
            "Step 2: insertEnd(): new node linked to rear->next; rear becomes new node.",
            "Step 3: insertPosition(): traverse to position - 1; splice new node between (temp) and (temp->next).",
            "Step 4: deleteBeginning(): head advances to head->next; old head freed.",
            "Step 5: deleteEnd(): traverse to second last node; set its next to NULL; free old rear.",
            "Step 6: deletePosition(): traverse to target node with prev pointer; link prev->next = temp->next; free temp.",
            "Step 7: display(), count(), and destroyList() to manage full list lifecycle."
        ],
        code_snippet="""// Insert at specific position
for (i = 1; i < position - 1 && t != NULL; i++) t = t->next;
n->next = t->next;
t->next = n;

// Delete from specific position
for (i = 1; i < position && t != NULL; i++) { prev = t; t = t->next; }
prev->next = t->next;
free(t);""",
        complexity="Beginning ops: O(1). End & Position ops: O(n).",
        exam_tip="Remember edge case for position = 1: if position == 1, simply delegate to insertBeginning() or deleteBeginning()."
    )

    add_topic(
        num=22,
        title="Doubly Linked List",
        file_name="Doubly_Linked_List.c",
        aim="To implement a Doubly Linked List with front, rear, and middle insertion and deletion.",
        concept="Each node contains data and two pointers: 'prev' (points to previous node) and 'next' (points to subsequent node).",
        steps=[
            "Step 1: Define struct Node { int data; struct Node *prev, *next; } and head = NULL.",
            "Step 2: insertFront(): allocate newNode. newNode->next = head; newNode->prev = NULL. If head != NULL, head->prev = newNode. Set head = newNode.",
            "Step 3: insertRear(): allocate newNode. Traverse to last node temp. Link temp->next = newNode; newNode->prev = temp.",
            "Step 4: insertMiddle(): find target node temp. Allocate newNode. Link: newNode->next = temp->next; newNode->prev = temp; if temp->next != NULL temp->next->prev = newNode; temp->next = newNode.",
            "Step 5: deleteFront(): head = head->next; if head != NULL head->prev = NULL; free old head.",
            "Step 6: deleteRear(): traverse to last node temp; temp->prev->next = NULL; free temp.",
            "Step 7: deleteMiddle(): find node temp. Unlink: if temp->prev != NULL temp->prev->next = temp->next; if temp->next != NULL temp->next->prev = temp->prev; free temp."
        ],
        code_snippet="""// Splice in middle:
newNode->next = temp->next;
newNode->prev = temp;
if (temp->next != NULL) temp->next->prev = newNode;
temp->next = newNode;

// Unlink in middle:
if (temp->prev != NULL) temp->prev->next = temp->next;
if (temp->next != NULL) temp->next->prev = temp->prev;
free(temp);""",
        complexity="Front ops: O(1). Rear & Middle ops: O(n).",
        exam_tip="Exam trap: Don't allocate memory for newNode in insertMiddle() until AFTER verifying that the target node exists!"
    )

    add_topic(
        num=23,
        title="Concatenate Two Linked Lists",
        file_name="Concatinate_Linked_List.c",
        aim="To concatenate (merge end-to-end) two separate singly linked lists.",
        concept="Traverse the first linked list to its tail node, and update its 'next' pointer to point to the head of the second linked list.",
        steps=[
            "Step 1: Create two independent linked lists: head1 and head2 using create().",
            "Step 2: Define concatenate(head1, head2):",
            "         a. If head1 == NULL, return head2.",
            "         b. If head2 == NULL, return head1.",
            "         c. Initialize temp = head1.",
            "         d. Traverse while (temp->next != NULL) temp = temp->next.",
            "         e. Link temp->next = head2.",
            "         f. Return head1.",
            "Step 3: Display the concatenated list."
        ],
        code_snippet="""struct Node *concatenate(struct Node *head1, struct Node *head2) {
    if (head1 == NULL) return head2;
    struct Node *temp = head1;
    while (temp->next != NULL) {
        temp = temp->next;
    }
    temp->next = head2;
    return head1;
}""",
        complexity="Time: O(n1) where n1 is the length of list 1. Auxiliary Space: O(1).",
        exam_tip="Viva Question: Do we need to traverse list 2? Answer: No, we only traverse list 1 to locate its last node; list 2 is attached directly at its head."
    )

    add_topic(
        num=24,
        title="Create Ordered (Sorted) Linked List",
        file_name="Create_Ordered_List.c",
        aim="To insert elements into a linked list such that it remains sorted in ascending order at all times.",
        concept="For every new element, search for the correct insertion position: either before the head (if smaller than head) or between two existing nodes.",
        steps=[
            "Step 1: Start with head = NULL.",
            "Step 2: For each input value, allocate newNode with data and next = NULL.",
            "Step 3: If head == NULL or newNode->data < head->data:",
            "         a. Insert at head: newNode->next = head; head = newNode.",
            "Step 4: Else:",
            "         a. Traverse temp = head while (temp->next != NULL and temp->next->data < newNode->data).",
            "         b. Splice node: newNode->next = temp->next; temp->next = newNode.",
            "Step 5: Repeat for all n elements, then display the sorted list."
        ],
        code_snippet="""if (head == NULL || newNode->data < head->data) {
    newNode->next = head;
    head = newNode;
} else {
    temp = head;
    while (temp->next != NULL && temp->next->data < newNode->data)
        temp = temp->next;
    newNode->next = temp->next;
    temp->next = newNode;
}""",
        complexity="Time: O(n) per insertion, leading to O(n^2) total for n elements. Space: O(1).",
        exam_tip="Notice the condition temp->next->data < newNode->data: checking one step ahead allows stopping exactly at the node prior to the insertion point."
    )

    add_topic(
        num=25,
        title="Reverse a Singly Linked List",
        file_name="Reverse_Linked_List.c",
        aim="To reverse the links of a singly linked list in-place using three pointers.",
        concept="Reverses the directional pointers of the list so that head becomes tail and tail becomes head, without allocating any extra nodes.",
        steps=[
            "Step 1: Start with head pointing to original list and prev = NULL, next = NULL.",
            "Step 2: Traverse while head != NULL:",
            "         a. Save next node: next = head->next.",
            "         b. Reverse pointer: head->next = prev.",
            "         c. Advance prev: prev = head.",
            "         d. Advance head: head = next.",
            "Step 3: Update head = prev (prev now points to the new head node).",
            "Step 4: Display the reversed list."
        ],
        code_snippet="""// The 4-line classic reversal algorithm:
while (head != NULL) {
    next = head->next;
    head->next = prev;
    prev = head;
    head = next;
}
head = prev;""",
        complexity="Time: O(n) linear scan. Space: O(1) in-place reversal.",
        exam_tip="This is one of the most frequently asked questions in both academic exams and tech interviews. Memorize the 4-line pointer swap: save next, reverse link, move prev, move head."
    )

    add_topic(
        num=26,
        title="Polynomial Representation & Evaluation",
        file_name="Polynomial_Represent_And_Evaluate.c",
        aim="To represent a polynomial as a linked list and evaluate its value for a given x.",
        concept="Each node represents a term: struct Node { int coeff, power; struct Node *next; }. Evaluation computes coeff * (x ^ power) for each node.",
        steps=[
            "Step 1: Define node structure storing coeff, power, and next.",
            "Step 2: create(): read number of terms; for each term, scan coeff and power, append at tail of linked list.",
            "Step 3: display(): traverse list and print terms formatted as coeff*x^power + ...",
            "Step 4: evaluate(poly, x):",
            "         a. Initialize result = 0.",
            "         b. While poly != NULL: result += poly->coeff * pow(x, poly->power); poly = poly->next.",
            "         c. Return result.",
            "Step 5: Print evaluated value."
        ],
        code_snippet="""int evaluate(struct Node *head, int x) {
    int result = 0;
    while (head != NULL) {
        result += head->coeff * (int)pow(x, head->power);
        head = head->next;
    }
    return result;
}""",
        complexity="Creation: O(n), Evaluation: O(n). Space: O(n).",
        exam_tip="Remember to cast pow() to (int) to prevent compiler floating-point conversion warnings."
    )

    add_topic(
        num=27,
        title="Polynomial Addition & Subtraction",
        file_name="Represent_And_Add_Sub_Polynomial.c",
        aim="To add and subtract two polynomials represented as singly linked lists.",
        concept="Simultaneously traverse both polynomials (a = p1, b = p2) comparing powers: if powers match, combine coefficients; otherwise output the term with the higher power.",
        steps=[
            "Step 1: Read and construct polynomials p1 and p2 sorted in descending order of powers.",
            "Step 2: add() / subtract(): Set pointers a = p1 and b = p2.",
            "Step 3: While a != NULL and b != NULL:",
            "         a. If a->power == b->power: print (a->coeff ± b->coeff) x^(a->power); advance both a and b.",
            "         b. If a->power > b->power: print a->coeff x^(a->power); advance a.",
            "         c. If b->power > a->power: print (±b->coeff) x^(b->power); advance b.",
            "Step 4: Print any remaining terms from list a or list b.",
            "Step 5: Stop."
        ],
        code_snippet="""while (a != NULL && b != NULL) {
    if (a->power == b->power) {
        printf("%dx^%d + ", a->coeff + b->coeff, a->power);
        a = a->next; b = b->next;
    } else if (a->power > b->power) {
        printf("%dx^%d + ", a->coeff, a->power);
        a = a->next;
    } else {
        printf("%dx^%d + ", b->coeff, b->power);
        b = b->next;
    }
}""",
        complexity="Time: O(n1 + n2). Space: O(1) when printing directly.",
        exam_tip="Notice how a single create() function is reused for both polynomials instead of writing duplicate create1() and create2() functions."
    )

    # ==========================================
    # SECTION 5: TREES & NON-RECURSIVE TRAVERSALS
    # ==========================================
    add_section_header("Section 5: Trees & Non-Recursive Traversals")

    add_topic(
        num=28,
        title="Binary Tree Array Representation & Traversals",
        file_name="Binary_Tree_And_Traversal.c",
        aim="To implement a Binary Tree using an array and perform recursive Preorder, Inorder, and Postorder traversals.",
        concept="Array indexing formula: Root is at index 0. For any node at index i: Left Child is at 2*i + 1, Right Child is at 2*i + 2.",
        steps=[
            "Step 1: Initialize tree[MAX] with all elements set to -1 (indicating empty node).",
            "Step 2: createTree(index): read data; if data == -1, return; set tree[index] = data; recursively create left child at 2*index + 1 and right child at 2*index + 2.",
            "Step 3: preorder(index): visit Root -> Preorder(Left) -> Preorder(Right).",
            "Step 4: inorder(index): Inorder(Left) -> visit Root -> Inorder(Right).",
            "Step 5: postorder(index): Postorder(Left) -> Postorder(Right) -> visit Root."
        ],
        code_snippet="""void preorder(int i) {
    if (i >= MAX || tree[i] == -1) return;
    printf("%d ", tree[i]);
    preorder(2 * i + 1);
    preorder(2 * i + 2);
}
void inorder(int i) {
    if (i >= MAX || tree[i] == -1) return;
    inorder(2 * i + 1);
    printf("%d ", tree[i]);
    inorder(2 * i + 2);
}""",
        complexity="Time: O(n) for all traversals. Space: O(h) recursion stack.",
        exam_tip="Array representation is memory-efficient only for Complete or Full Binary Trees. For skewed trees, it wastes significant array space."
    )

    add_topic(
        num=29,
        title="Binary Search Tree (Add, Search, Min, Max)",
        file_name="BST_Min_Max.c",
        aim="To implement a Binary Search Tree (BST) supporting insertion, key search, finding minimum, and finding maximum.",
        concept="BST Invariant: For every node, left subtree values < node value < right subtree values. Inorder traversal of a BST always yields sorted order.",
        steps=[
            "Step 1: Define struct Node { int data; struct Node *left, *right; }.",
            "Step 2: addNode(root, data):",
            "         a. If root == NULL, return createNode(data).",
            "         b. If data < root->data, root->left = addNode(root->left, data).",
            "         c. If data > root->data, root->right = addNode(root->right, data).",
            "         d. Return root.",
            "Step 3: search(root, target): if root == NULL, 'Not Found'; if target == root->data, 'Found'; if target < root->data, search left; else search right.",
            "Step 4: findMin(root): traverse left pointers (while root->left != NULL root = root->left); return root->data.",
            "Step 5: findMax(root): traverse right pointers (while root->right != NULL root = root->right); return root->data."
        ],
        code_snippet="""int findMin(struct Node *root) {
    while (root->left != NULL) root = root->left;
    return root->data;
}
int findMax(struct Node *root) {
    while (root->right != NULL) root = root->right;
    return root->data;
}""",
        complexity="Search/Insert/Min/Max: O(h) where h = height of tree (O(log n) average, O(n) worst case for skewed tree).",
        exam_tip="Viva Question: Where is the minimum and maximum value located in a BST? Answer: Minimum is the leftmost node; Maximum is the rightmost node."
    )

    add_topic(
        num=30,
        title="Non-Recursive Preorder Traversal",
        file_name="Preorder_Traversal_Non_Recursive.c",
        aim="To traverse a binary tree iteratively in Preorder (Root -> Left -> Right) using an explicit pointer stack.",
        concept="Uses 1 stack. Pop a node, print it, push its right child first, then push its left child (so left is popped and processed first).",
        steps=[
            "Step 1: If root == NULL, return.",
            "Step 2: Initialize stack of node pointers with top = -1.",
            "Step 3: Push root onto stack (stack[++top] = root).",
            "Step 4: While stack is not empty (top != -1):",
            "         a. Pop node: temp = stack[top--].",
            "         b. Print temp->data.",
            "         c. If temp->right != NULL, push temp->right.",
            "         d. If temp->left != NULL, push temp->left.",
            "Step 5: Stop."
        ],
        code_snippet="""void preorder(struct Node *root) {
    if (!root) return;
    struct Node *stack[100]; int top = -1;
    stack[++top] = root;
    while (top != -1) {
        struct Node *temp = stack[top--];
        printf("%d ", temp->data);
        if (temp->right) stack[++top] = temp->right;
        if (temp->left)  stack[++top] = temp->left;
    }
}""",
        complexity="Time: O(n). Space: O(h) stack depth.",
        exam_tip="Why push right child before left child? Answer: Because a stack is LIFO. Pushing right first ensures that the left child sits on top of the stack and is visited next."
    )

    add_topic(
        num=31,
        title="Non-Recursive Inorder Traversal",
        file_name="Inorder_Traversal_Non_Recursive.c",
        aim="To traverse a binary tree iteratively in Inorder (Left -> Root -> Right) using 1 stack.",
        concept="Reach the leftmost leaf while pushing all nodes along the path. When NULL is reached, pop node, print it, and move to its right subtree.",
        steps=[
            "Step 1: Initialize stack with top = -1, and pointer temp = root.",
            "Step 2: Loop while temp != NULL or top != -1:",
            "         a. While temp != NULL: push temp onto stack; temp = temp->left.",
            "         b. Pop node: temp = stack[top--].",
            "         c. Print temp->data.",
            "         d. Advance to right child: temp = temp->right.",
            "Step 3: Stop."
        ],
        code_snippet="""void inorder(struct Node *root) {
    struct Node *stack[100]; int top = -1;
    struct Node *temp = root;
    while (temp != NULL || top != -1) {
        while (temp != NULL) {
            stack[++top] = temp;
            temp = temp->left;
        }
        temp = stack[top--];
        printf("%d ", temp->data);
        temp = temp->right;
    }
}""",
        complexity="Time: O(n). Space: O(h) stack depth.",
        exam_tip="The inner while loop explores down the left spine of the subtree as far as possible before printing any node."
    )

    add_topic(
        num=32,
        title="Non-Recursive Postorder Traversal",
        file_name="Postorder_Traversal_Non_Recursive.c",
        aim="To traverse a binary tree iteratively in Postorder (Left -> Right -> Root) using two stacks.",
        concept="Postorder (Left -> Right -> Root) is the exact reverse of modified Preorder (Root -> Right -> Left). Stack 1 processes nodes, and Stack 2 stores them in reverse for printing.",
        steps=[
            "Step 1: If root == NULL, return.",
            "Step 2: Initialize stack1 and stack2 with top1 = -1, top2 = -1.",
            "Step 3: Push root onto stack1.",
            "Step 4: While stack1 is not empty:",
            "         a. Pop temp from stack1.",
            "         b. Push temp onto stack2.",
            "         c. If temp->left != NULL, push temp->left onto stack1.",
            "         d. If temp->right != NULL, push temp->right onto stack1.",
            "Step 5: While stack2 is not empty:",
            "         a. Pop temp from stack2 and print temp->data.",
            "Step 6: Stop."
        ],
        code_snippet="""void postorder(struct Node *root) {
    if (!root) return;
    struct Node *s1[100], *s2[100]; int t1 = -1, t2 = -1;
    s1[++t1] = root;
    while (t1 != -1) {
        struct Node *temp = s1[t1--];
        s2[++t2] = temp;
        if (temp->left)  s1[++t1] = temp->left;
        if (temp->right) s1[++t1] = temp->right;
    }
    while (t2 != -1) {
        printf("%d ", s2[t2--]->data);
    }
}""",
        complexity="Time: O(n). Space: O(n) for stack 2.",
        exam_tip="Why is the 2-stack method preferred in exams over the 1-stack method? Answer: 1-stack postorder requires complex parent tracking or flag markers, whereas 2-stack postorder is clean, bug-free, and easy to memorize."
    )

    # Save Document
    filename = "DSA_Exam_Algorithms_Guide.docx"
    doc.save(filename)
    print(f"Document successfully created and saved as: {filename}")

if __name__ == "__main__":
    create_exam_guide()
