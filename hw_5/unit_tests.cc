#include <fstream>
#include "gtest/gtest.h"
#include "typed_array.h"
#include "utilities.h"

namespace {

// Test for sort_by_magnitude function
TEST(UtilitiesTest, SortByMagnitude) {
    std::vector<double> vec = {-3, 1, -2, 4};
    sort_by_magnititude(vec);
    std::vector<double> expected = {1, -2, -3, 4};
    EXPECT_EQ(vec, expected);
}

// Test for read_matrix_csv with a non-existent file
TEST(UtilitiesTest, ReadMatrixCsvNonExistentFile) {
    ASSERT_THROW({ read_matrix_csv("non_existent_file.csv"); },
                 std::runtime_error);
}

// Test for read_matrix_csv with a file that has inconsistent row lengths
TEST(UtilitiesTest, ReadMatrixCsvInconsistentRows) {
    // Assuming "inconsistent_matrix.csv" exists and has rows of different lengths 
    ASSERT_THROW({
        read_matrix_csv("inconsistent_matrix.csv");
    }, std::runtime_error);
}

// Test for read_matrix_csv with a file that contains invalid numbers
TEST(UtilitiesTest, ReadMatrixCsvInvalidNumbers) {
    // Assuming "invalid_numbers_matrix.csv" exists and contains invalid numbers 
    ASSERT_THROW({
        read_matrix_csv("invalid_numbers_matrix.csv");
    }, std::runtime_error);
}

// Test for read_matrix_csv with a file that contains missing values
TEST(UtilitiesTest, ReadMatrixCsvMissingValues) {
    // Assuming "missing_values_matrix.csv" exists and contains missing values 
    ASSERT_THROW({
        read_matrix_csv("missing_numbers_matrix.csv");
    }, std::runtime_error);
}

// Test for read_matrix_csv with a file that contains trimming numbers
TEST(MatrixReadTest, HandlesTrimmingNumbers) {
    auto matrix = read_matrix_csv("trim_numbers_matrix.csv");
    ASSERT_EQ(matrix.size(), 3);
    ASSERT_EQ(matrix.get(0).size(), 3);
    EXPECT_DOUBLE_EQ(matrix.get(0).get(0), 1.0);
    EXPECT_DOUBLE_EQ(matrix.get(0).get(1), 2.0);
    EXPECT_DOUBLE_EQ(matrix.get(0).get(2), 3.0);
    EXPECT_DOUBLE_EQ(matrix.get(1).get(0), 4.5);
    EXPECT_DOUBLE_EQ(matrix.get(1).get(1), 5.5);
    EXPECT_DOUBLE_EQ(matrix.get(1).get(2), 6.7);
    EXPECT_DOUBLE_EQ(matrix.get(2).get(0), 7.0);
    EXPECT_DOUBLE_EQ(matrix.get(2).get(1), 8.0);
    EXPECT_DOUBLE_EQ(matrix.get(2).get(2), 9.0);
}

// Test for read and write matrix to CSV
TEST(MatrixReadWriteTest, WriteAndReadBack) {

    TypedArray<TypedArray<double>> matrix;
    TypedArray<double> row1, row2;
    row1.set(0, 1.0); row1.set(1, 2.0);
    row2.set(0, 3.0); row2.set(1, 4.0);
    matrix.set(0, row1);
    matrix.set(1, row2);

    std::string tempFilePath = "temp_matrix.csv";

    write_matrix_csv(matrix, tempFilePath);

    TypedArray<TypedArray<double>> matrixReadBack =
    read_matrix_csv(tempFilePath);

    ASSERT_EQ(matrixReadBack.size(), matrix.size());
    for (size_t i = 0; i < matrix.size(); ++i) {
        ASSERT_EQ(matrixReadBack.get(i).size(), matrix.get(i).size());
        for (size_t j = 0; j < matrix.get(i).size(); ++j) {
            EXPECT_DOUBLE_EQ(matrixReadBack.get(i).get(j),
            matrix.get(i).get(j));
        }
    }

    std::remove(tempFilePath.c_str());
}

// Test for occurrence_map function
TEST(UtilitiesTest, OccurrenceMapExamples) {
    auto wordCount = occurrence_map("test_text.txt");
    // Test for valid keys
    EXPECT_EQ(wordCount["this"], 1);
    EXPECT_EQ(wordCount["sentence"], 1);
    EXPECT_EQ(wordCount["don't"], 1);
    EXPECT_EQ(wordCount["think"], 1);
    EXPECT_EQ(wordCount["of"], 2);
    EXPECT_EQ(wordCount["strings"], 1);
    EXPECT_EQ(wordCount["as"], 2);
    EXPECT_EQ(wordCount["words"], 1);
    EXPECT_EQ(wordCount["really"], 1);
    EXPECT_EQ(wordCount["123"], 1);
    EXPECT_EQ(wordCount["is"], 4);
    EXPECT_EQ(wordCount["a"], 4);
    EXPECT_EQ(wordCount["nice"], 1);
    EXPECT_EQ(wordCount["mallory's"], 1);
    EXPECT_EQ(wordCount["state"], 1);
    EXPECT_EQ(wordCount["constant"], 1);
    EXPECT_EQ(wordCount["rebellion"], 1);
    EXPECT_EQ(wordCount["10xgenomics"], 1);
    EXPECT_EQ(wordCount["biotech"], 1);
    EXPECT_EQ(wordCount["company"], 1);
    EXPECT_EQ(wordCount["quoted"], 1);
    EXPECT_EQ(wordCount["saying"], 1);
    EXPECT_EQ(wordCount["blah"], 3);
    EXPECT_EQ(wordCount["are"], 1);

    // Test for invalid strings -- these should not appear in the wordCount map
    EXPECT_EQ(wordCount.find("wier_d"), wordCount.end());
    EXPECT_EQ(wordCount.find("the)s"), wordCount.end());
    EXPECT_EQ(wordCount.find("no%y6"), wordCount.end());
    EXPECT_EQ(wordCount.find("wo!e4"), wordCount.end());
}

int main(int argc, char** argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}

}  // namespace