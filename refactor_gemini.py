import os
import time
import google.generativeai as genai
from pathlib import Path

# --- 설정 (Configuration) ---
# 1. API 키 설정 (환경 변수에서 가져오기)
api_key = os.getenv("GEMINI_API_KEY")
if not api_key:
    raise ValueError("터미널에서 GEMINI_API_KEY 환경 변수를 설정해주세요.")
genai.configure(api_key=api_key)

# 2. 리팩토링할 소스 코드 경로 설정 (Minix 소스가 있는 폴더 이름)
source_directory = Path("./source")

# 3. 리팩토링 프롬프트
refactoring_prompt = """You are an expert C programmer specializing in improving legacy code for SonarCloud analysis. Refactor the following C code to improve its Maintainability and Reliability. Focus on simplifying complex logic, removing code smells, and ensuring proper error handling, without altering its external functionality. Return ONLY the refactored C code, without any explanation, comments, or markdown formatting like ```c. Just the raw code."""

# --- 실행 (Execution) ---
model = genai.GenerativeModel('gemini-1.5-pro-latest')

# 대상 파일 찾기
files_to_refactor = list(source_directory.rglob("*.c")) + list(source_directory.rglob("*.h"))
total_files = len(files_to_refactor)
print(f"총 {total_files}개의 파일을 리팩토링합니다...")

for i, file_path in enumerate(files_to_refactor):
    try:
        print(f"[{i+1}/{total_files}] 처리 중: {file_path}")

        with open(file_path, 'r', encoding='utf-8', errors='ignore') as f:
            original_code = f.read()

        # Gemini API 호출
        full_prompt = refactoring_prompt + "\n\n---\n\n" + original_code
        response = model.generate_content(full_prompt)

        # 결과물로 원본 파일 덮어쓰기
        with open(file_path, 'w', encoding='utf-8') as f:
            f.write(response.text)

        # SonarCloud 무료 플랜의 속도 제한(RPM)을 준수하기 위한 대기
        print("...완료. 다음 파일을 위해 1.2초 대기합니다.")
        time.sleep(1.2)

    except Exception as e:
        print(f"!!! 오류 발생: {file_path} 처리 중 문제 발생 - {e}")
        print("...1.2초 후 다음 파일로 넘어갑니다.")
        time.sleep(1.2) # 오류 시에도 대기

print("모든 파일의 리팩토링 작업이 완료되었습니다.")
