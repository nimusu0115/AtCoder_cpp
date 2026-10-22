"""C++17 differential tests and independent copy/paste compilation (no packages)."""
import argparse
import os
from pathlib import Path
import subprocess
import tempfile

ROOT = Path(__file__).resolve().parents[1]


def run(command, timeout=120):
    subprocess.run([str(x) for x in command], check=True, timeout=timeout, cwd=ROOT.parent)


def main():
    parser = argparse.ArgumentParser()
    parser.add_argument('--compiler', default=os.environ.get('CXX', 'g++'))
    parser.add_argument('--snippets', action='store_true')
    parser.add_argument('--ubsan', action='store_true')
    parser.add_argument('--debug-stl', action='store_true')
    args = parser.parse_args()
    flags = ['-std=c++17', '-O2', '-Wall', '-Wextra', '-I', str(ROOT.parent)]
    if args.ubsan:
        flags += ['-fsanitize=undefined', '-fno-sanitize-recover=all']
    if args.debug_stl:
        flags += ['-D_GLIBCXX_DEBUG', '-D_GLIBCXX_ASSERTIONS']
    suffix = '.exe' if os.name == 'nt' else ''
    with tempfile.TemporaryDirectory(prefix='atcoder-library-') as directory:
        temp = Path(directory)
        for source in sorted((ROOT / 'tests').glob('test_*.cpp')):
            print(f'TEST {source.name}', flush=True)
            exe = temp / (source.stem + suffix)
            run([args.compiler, *flags, source, '-o', exe])
            run([exe])
        for source in sorted((ROOT / 'examples').glob('*.cpp')):
            print(f'EXAMPLE {source.name}', flush=True)
            exe = temp / (source.stem + suffix)
            run([args.compiler, *flags, source, '-o', exe])
            fixtures = {
                'scc_pairs.cpp': ('4 5\n1 2\n2 1\n2 3\n3 4\n4 3\n', '2\n'),
                'digit_dp.cpp': ('20\n', '6\n'),
            }
            sample_input, expected = fixtures.get(source.name, ('', ''))
            result = subprocess.run([str(exe)], input=sample_input, text=True,
                                    capture_output=True, check=True, timeout=30)
            assert result.stdout == expected, (source.name, result.stdout, expected)
        if args.snippets:
            sources = sorted(p for p in ROOT.glob('*/*.cpp') if p.parent.name not in {'tests', 'examples'})
            for source in sources:
                print(f'SNIPPET {source.relative_to(ROOT)}', flush=True)
                unit = temp / 'snippet.cpp'
                unit.write_text(source.read_text(encoding='utf-8') + '\nint main() {}\n', encoding='utf-8')
                exe = temp / ('snippet' + suffix)
                run([args.compiler, *flags, unit, '-o', exe])
                run([exe])
            print(f'{len(sources)} independent snippets compiled and ran.', flush=True)
            unit = temp / 'combined.cpp'
            unit.write_text('\n'.join(p.read_text(encoding='utf-8') for p in sources)
                            + '\nint main() {}\n', encoding='utf-8')
            exe = temp / ('combined' + suffix)
            run([args.compiler, *flags, unit, '-o', exe])
            run([exe])
            print('Combined copy/paste compilation passed.', flush=True)
    print('All checks passed.', flush=True)


if __name__ == '__main__':
    main()
