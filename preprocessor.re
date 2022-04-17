
#include <string>
#include "input.h"
#include <stdexcept>
#include <iostream>
#include "utils.h"
#include <filesystem>

using std::cerr, std::cout, std::filesystem::path;

#define line_marking(f, l) "# \"" << f << "\" " << l << "\n"

/*!re2c re2c:define:YYCTYPE = "unsigned char"; */
/*!maxnmatch:re2c*/


int preprocess(const std::string &filename, std::ostream &out) {
    int line_no = 1;

    struct input_t in(filename, /*!max:re2c format="@@";*/+0);  // +0 just to avoid ide errors

    out << line_marking(filename, line_no);

    path parent = path(filename).parent_path();

    for (;;) {
        in.tok = in.cur;
        const unsigned char *yypmatch[YYMAXNMATCH * 2];
        size_t yynmatch;

        /*!stags:re2c format = 'const unsigned char *@@;\n'; */

        /*!re2c
            re2c:yyfill:enable = 1;
            re2c:define:YYCURSOR = in.cur;
            re2c:define:YYMARKER = in.mar;
            re2c:define:YYLIMIT = in.lim;
            re2c:define:YYFILL = "if (!in.fill(@@)) return false;";
            re2c:define:YYFILL:naked = 1;
            re2c:posix-captures = 1;

            end = "\x00";

            *   { return 1; }
            end {
                out << "\n";
                return 0;
            }

            ("/*" (([^*] | ("*" [^/]))*) "*""/") {
                for (const unsigned char *s = yypmatch[2]; s < yypmatch[3]; s++) {
                    if (*s == '\n') {
                        line_no++;
                    }
                }

                out << line_marking(filename, line_no);
                continue;
            }

            ("//" [^\n]* "\n") {
                out << '\n';
                continue;
            }

            "#include \"" (.+) "\"" {
                path inc_file(extract_match(yypmatch[2], yypmatch[3]));
                try {
                    preprocess((parent / inc_file).string(), out);
                } catch(...) {
                    cerr << filename << ":" << line_no << ":" << inc_file.string() << "does not exist";
                    continue;
                }

                out << line_marking(filename, line_no);
                continue;
            }

            "\n" {
                out << "\n";
                line_no++;
                continue;
            }

            [^] {out << *(in.tok);continue;}
        */
    }

    return 0;
}