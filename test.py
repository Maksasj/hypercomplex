import subprocess
import os

def compile_test(test_folder_path):
      print("Compiling Test: ", test_folder_path)
      subprocess.check_output(['g++','-o',test_folder_path+'test',test_folder_path+'test.cpp'])
      subprocess.check_call([test_folder_path+'test.exe'])

def get_tests():
      tests_list = os.listdir('tests/')
      return tests_list

def print_detail_difference(file_1_line, file_2_line, line_no):
      if file_1_line == '':
            print("@", "Line-%d" % line_no, file_1_line)
      else:
            print("@-", "Line-%d" % line_no, file_1_line)

      if file_2_line == '':
            print("#", "Line-%d" % line_no, file_2_line)
      else:
            print("#+", "Line-%d" % line_no, file_2_line)

def run_single_test(test_folder_path):
      output_filepath = test_folder_path+'output.txt'
      expected_output = test_folder_path+'expected_output.txt'
      file_1 = open(output_filepath, 'r')
      file_2 = open(expected_output, 'r')
      
      file_1_line = file_1.readline()
      file_2_line = file_2.readline()

      line_no = 1

      with open(output_filepath) as file1:
            with open(expected_output) as file2:
                  same = set(file1).intersection(file2)
      
      test_result = False
      
      while file_1_line != '' or file_2_line != '':
            file_1_line = file_1_line.rstrip()
            file_2_line = file_2_line.rstrip()

            if file_1_line != file_2_line:
                  print_detail_difference(file_1_line, file_2_line, line_no)
                  test_result = True

            file_1_line = file_1.readline()
            file_2_line = file_2.readline()
      
            line_no += 1

      if test_result == True:
            print("Test Failed: "+test_folder_path)

      file_1.close()
      file_2.close()

def run_test():
      tests_list = get_tests()

      for test in tests_list:
            test_path = 'tests/'+test+'/'

            compile_test(test_path)
            run_single_test(test_path)

run_test()