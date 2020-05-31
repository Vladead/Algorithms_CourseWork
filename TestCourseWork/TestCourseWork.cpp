#include "pch.h"
#include "CppUnitTest.h"
#include "../FordFalkerson.cpp"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace TestCourseWork
{
	TEST_CLASS(TestCourseWork)
	{
	private:
		FordFalkerson testObj;

		ifstream testInput;

	public:
		TEST_METHOD(test_buildListOfNodes)
		{
			testInput.open("C:\\Users\\vlade\\source\\repos\\CourseWork\\TestCourseWork\\firstExample.txt");
			testObj.buildListOfNodes(testInput);
			Assert::AreEqual(testObj.listOfNodes.get_pointer(0)->data, static_cast<string>("S"));
			Assert::AreEqual(testObj.listOfNodes.get_pointer(1)->data, static_cast<string>("A"));
			Assert::AreEqual(testObj.listOfNodes.get_pointer(2)->data, static_cast<string>("B"));
			Assert::AreEqual(testObj.listOfNodes.get_pointer(3)->data, static_cast<string>("T"));
			testInput.close();
		}

		TEST_METHOD(test_buildAdjacencyMatrix)
		{
			testInput.open("C:\\Users\\vlade\\source\\repos\\CourseWork\\TestCourseWork\\firstExample.txt");
			testObj.buildListOfNodes(testInput);
			testInput.close();

			testInput.open("C:\\Users\\vlade\\source\\repos\\CourseWork\\TestCourseWork\\firstExample.txt");
			testObj.buildAdjacencyMatrix(testInput);
			testInput.close();

			Assert::AreEqual(testObj.adjacencyMatrix[0][1], 9);
			Assert::AreEqual(testObj.adjacencyMatrix[0][2], 8);
			Assert::AreEqual(testObj.adjacencyMatrix[0][1], 9);
			Assert::AreEqual(testObj.adjacencyMatrix[1][2], 7);
			Assert::AreEqual(testObj.adjacencyMatrix[1][3], 6);
			Assert::AreEqual(testObj.adjacencyMatrix[2][3], 5);
		}

		TEST_METHOD(test_isTransportNet_true)
		{
			testInput.open("C:\\Users\\vlade\\source\\repos\\CourseWork\\TestCourseWork\\firstExample.txt");
			testObj.buildListOfNodes(testInput);
			testInput.close();

			testInput.open("C:\\Users\\vlade\\source\\repos\\CourseWork\\TestCourseWork\\firstExample.txt");
			testObj.buildAdjacencyMatrix(testInput);
			testInput.close();

			Assert::IsTrue(testObj.isTransportNet());
		}

		TEST_METHOD(test_isTransportNet_false)
		{
			testInput.open("C:\\Users\\vlade\\source\\repos\\CourseWork\\TestCourseWork\\notTransportNet.txt");
			testObj.buildListOfNodes(testInput);
			testInput.close();

			testInput.open("C:\\Users\\vlade\\source\\repos\\CourseWork\\TestCourseWork\\notTransportNet.txt");
			testObj.buildAdjacencyMatrix(testInput);
			testInput.close();

			Assert::IsFalse(testObj.isTransportNet());
		}

		TEST_METHOD(test_walkInDepth)
		{
			testInput.open("C:\\Users\\vlade\\source\\repos\\CourseWork\\TestCourseWork\\firstExample.txt");
			testObj.buildListOfNodes(testInput);
			testInput.close();

			testInput.open("C:\\Users\\vlade\\source\\repos\\CourseWork\\TestCourseWork\\firstExample.txt");
			testObj.buildAdjacencyMatrix(testInput);
			testInput.close();

			int maxFlow = 0;
			maxFlow = testObj.getMaxFlow();

			Assert::AreEqual(maxFlow, 11);
		}

		TEST_METHOD(test_walkInDepth_1)
		{
			testInput.open("C:\\Users\\vlade\\source\\repos\\CourseWork\\TestCourseWork\\secondExample.txt");
			testObj.buildListOfNodes(testInput);
			testInput.close();

			testInput.open("C:\\Users\\vlade\\source\\repos\\CourseWork\\TestCourseWork\\secondExample.txt");
			testObj.buildAdjacencyMatrix(testInput);
			testInput.close();

			int maxFlow = 0;
			maxFlow = testObj.getMaxFlow();

			Assert::AreEqual(maxFlow, 29);
		}

		TEST_METHOD(test_makeAllFalse)
		{
			testObj.makeAllFalse();
			for (int i = 0; i < testObj.listOfMarks.get_size(); i++)
			{
				Assert::IsFalse(testObj.listOfMarks.get_pointer(i)->data);
			}
		}
	};
}
