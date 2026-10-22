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
    args = parser.parse_args()
    flags = ['-std=c++17', '-O2', '-Wall', '-Wextra', '-I', str(ROOT.parent)]
    if args.ubsan:
        flags += ['-fsanitize=undefined', '-fno-sanitize-recover=all']
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
            # 入力を読む例はEOFで終了する実装にする。
            subprocess.run([str(exe)], input='', text=True, check=True, timeout=30)
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
    print('All checks passed.', flush=True)


if __name__ == '__main__':
    main()
